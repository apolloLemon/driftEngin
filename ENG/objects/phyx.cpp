#include "phyx.h"
#include <iostream>
static const int PHYX_LAYER=0;

void PhyxENG::Init(std::vector<GameObj*>* gameobjects, CollisionENG *ce,SoundENG *se){
	managed.clear();
	for (unsigned int i = 0; i < gameobjects->size(); i++)
	{
		GameObj* go = gameobjects->at(i);
		PhyxObj2D* cast = dynamic_cast<PhyxObj2D *>(go);
		if(cast) managed.push_back(cast);
	}
	collisionENG = ce;
	soundENG = se;
}

void PhyxENG::Update(){
	auto tn = std::chrono::steady_clock::now();
	std::chrono::duration<double, std::milli> d = tn - t;
	double dd = d.count()/1000;
	t=tn;

	int cols=0;
	for(int i=0;i<managed.size();i++){
			PhyxObj2D * p = managed[i];
		for(int j=i+1;j<managed.size();j++){ //this kind of loop allows us to only check a couple once
			PhyxObj2D * q = managed[j];
			
			//Global Forces between all objects
			//maybe give the PhyxENG settings to toggle these
			glm::dvec2 g = PhyxENG::Gravity2D(*p,*q);
			p->AddForce(g);
			q->AddForce(-g);


			CollisionMsg * pqData = collisionENG->CollisionBetween(p,q,PHYX_LAYER);
			if(pqData){
				cols++;
				if(soundENG && glm::length(glm::dot(p->v,q->v))>0.5){
						soundENG->Play(2, false);
					}
				StaticResolution(pqData->P.second,pqData->Q.second);
				DynamicResolution(p,pqData->P.second, q,pqData->Q.second);
			}
		}
		//now that i has seen all the other phyxObj, he's finished working
		p->Update(dd);
		p->ResetA();
	}
//	if(cols) std::cout<<"collision count"<<cols<<std::endl;
}

void PhyxENG::StaticResolution(Collider *p,Collider *q){
	glm::dvec2 p2q = p->worldPosition() - q->worldPosition();
	glm::dvec2 nor = glm::normalize(p2q);

	CircleCollider *pc = dynamic_cast<CircleCollider *>(p);
	CircleCollider *qc = dynamic_cast<CircleCollider *>(q);
	if(pc&&qc){
		double overlap = (pc->Dim() + qc->Dim())-glm::length(p2q);
		p->Move(nor * overlap*.5);
		q->Move(nor*-1. * overlap*.5);
	} else {
		//at least try
		p->Move(nor);
		q->Move(nor*-1.);
	}

}

void PhyxENG::DynamicResolution(PhyxObj2D* p, Collider * pc,PhyxObj2D*q, Collider *qc){
	glm::dvec2 p2q = pc->worldPosition() - qc->worldPosition();
	glm::dvec2 nor = glm::normalize(p2q);

	CircleCollider *pcc = dynamic_cast<CircleCollider *>(pc);
	CircleCollider *qcc = dynamic_cast<CircleCollider *>(qc);
	if(pcc&&qcc){
		glm::dvec2 tan = glm::vec2(nor.y*-1.,nor.x);
		
		double pdottan = glm::dot(p->V(),tan);
		double qdottan = glm::dot(q->V(),tan);
		double pdotnor = glm::dot(p->V(),nor);
		double qdotnor = glm::dot(q->V(),nor);

		double pmomentum = (pdotnor*(p->mass - q->mass) + 2.*q->mass*qdotnor)/(p->mass+q->mass);
		double qmomentum = (qdotnor*(q->mass - p->mass) + 2.*p->mass*pdotnor)/(p->mass+q->mass);

		p->v = (tan*pdottan + nor*pmomentum);
		q->v = (tan*qdottan + nor*qmomentum);
		//*/
		/*/wikipedia method2:
		glm::dvec2 px2qx = p->pos2D-q->pos2D;
		double px2qxl = glm::length(px2qx);
		double px2qxl2 = px2qxl*px2qxl;
		glm::dvec2 pv2qv = p->v-q->v;
		double masssum =p->mass+q->mass;
		p->v -= (
				(2*q->mass/(masssum))
				*(
					glm::dot(pv2qv, px2qx) / px2qxl2
				) * px2qx
			);


		p->v -= (
				(2*p->mass/(masssum))
				*(
					glm::dot(pv2qv*-1., px2qx*-1.) / px2qxl2
				) * px2qx*-1.
			);
		//*/


	} else {
		//at least try
		p->ResetV();
		q->ResetV();
		p->ResetA();
		q->ResetA();
	}
}

glm::vec2 PhyxENG::Gravity2D(PhyxObj2D a,PhyxObj2D b) {
	glm::vec2 a2 = glm::vec2(a.X(),a.Y());
	glm::vec2 b2 = glm::vec2(b.X(),b.Y());
	glm::vec2 a2b = b2-a2;
	float G = 1;//6.67408/100000000000.;
	float Mm = a.Mass()*b.Mass();
	float d = glm::length(a2b);
	float r2 = (d*d)/4.f;
	return a2b*(G*(Mm/r2));
}




void PhyxObj2D::Update(double dt){	
	v += a * dt;
	Move(v*dt);
//	position += glm::vec3(v.x*dt,0,v.y*dt);
	//if(Speed()<0.00001) v=glm::vec2(0,0);
}
void PhyxObj2D::ResetA(){a=glm::vec2(0);}
void PhyxObj2D::ResetV(){v=glm::vec2(0);}
void PhyxObj2D::AddForce(glm::dvec2 _a) {
	a+=_a/mass;
}