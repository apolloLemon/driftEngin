#include "phyx.h"
#include <iostream>

/*/
PhyxObj2D::PhyxObj2D()
{
	xv = 0;
	yv = 0;
	xa = 0;
	ya = 0;
}//*/
void PhyxENG::Init(){
	for(auto go : gameobjects) {
		PhyxObj2D* cast = dynamic_cast<PhyxObj2D *>(go);
		if(cast) managed.push_back(cast);
	}
}


void PhyxENG::Update(){
	auto tn = std::chrono::steady_clock::now();
	//if(t==NULL) t=tn;

	//double d = std::chrono::duration_cast<double, std::milli> d = tn - t;
	std::chrono::duration<double, std::milli> d = tn - t;
	double dd = d.count()/1000;
	t=tn;

	for(auto p : managed){
		//if(!(p->actif)) continue;
		if(p->orbiting){
			//glm::vec2 g = PhyxENG::Gravity2D(*p,(*(p->orbiting)));
			//p->AddForce(g);
			if(p->orbiting->collider.isin(p->collider)){
				CollisionMsg colmsg = p->orbiting->collider.collision(p->collider);
				

				//std::cout << "Collision: " << colmsg.overlap<<" deep" << std::endl;
				

				p->pos2D += colmsg.nor * colmsg.overlap;
				double dot = glm::dot(colmsg.tan,p->V());
				p->XV(colmsg.tan.x*dot*.8);
				p->YV(colmsg.tan.y*dot*.8);
			//	p->AddForce(g*-1.f);

			}
		}
	}
	for(auto p : managed)
		for(auto q : managed)
			if(p!=q && p->orbiting!=q && q->orbiting!=p)
				if(p->collider.isin(q->collider)){
					std::cout <<"normal col\n";
					CollisionMsg colmsg = p->collider.collision(q->collider);

					p->pos2D -= colmsg.nor * colmsg.overlap/2.;
					q->pos2D += colmsg.nor * colmsg.overlap/2.;

					//*
					double pdottan = glm::dot(p->V(),colmsg.tan);
					double qdottan = glm::dot(q->V(),colmsg.tan);
					double pdotnor = glm::dot(p->V(),colmsg.nor);
					double qdotnor = glm::dot(q->V(),colmsg.nor);

					double pmomentum = (pdotnor*(p->mass - q->mass) + 2.*q->mass*qdotnor)/(p->mass+q->mass);
					double qmomentum = (qdotnor*(q->mass - p->mass) + 2.*p->mass*pdotnor)/(p->mass+q->mass);

					std::cout <<"0 "<<p->name<<": "<< glm::length(p->v) <<"\t"<<q->name<<": "<< glm::length(q->v)<<std::endl;
					p->v = (colmsg.tan*pdottan + colmsg.nor*pmomentum);
					q->v = (colmsg.tan*qdottan + colmsg.nor*qmomentum);
					std::cout <<"1 "<<p->name<<": "<< glm::length(p->v) <<"\t"<<q->name<<": "<< glm::length(q->v)<<std::endl;
					//*/
					/*/wikipedia method:
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
				}

	for(auto p : managed){
		p->Update(dd);
		p->ResetA();
	}
}

void PhyxObj2D::Update(double dt){
	pos2D += v*dt;
	collider.pos = pos2D;
	worldPosition = glm::vec3(pos2D.x,0,pos2D.y);


	v += a * dt;

	//if(Speed()<0.00001) v=glm::vec2(0,0);
}

void PhyxObj2D::Init(){
	pos2D=worldPosition;
	collider.pos = pos2D;
}

/*/
double const PhyxObj2D::V() {
	return std::pow(
				std::pow(xv,2)+std::pow(yv,2),
			.5);
}//*/

void PhyxObj2D::ResetA(){
	a=glm::vec2(0,0);
	//xa=0; ya=0;
}


void PhyxObj2D::AddForce(glm::dvec2 _a) {
	a+=_a/mass;
}
/*/
void PhyxObj2D::AddForce(double _x, double _y) {
	xa += _x;
	ya += _y;
}
//*/





glm::vec2 PhyxENG::Gravity2D(PhyxObj2D a,PhyxObj2D b) {
	glm::vec2 a2 = glm::vec2(a.X(),a.Y());
	glm::vec2 b2 = glm::vec2(b.X(),b.Y());
	glm::vec2 a2b = b2-a2;
	float G = 1;//6.67408f/100000000000.f;
	float Mm = a.Mass()*b.Mass();
	float d = glm::length(a2b);
	float r2 = (d*d)/4.f;
	return a2b*(G*(Mm/r2));
}