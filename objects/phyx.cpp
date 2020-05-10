#include "phyx.h"

/*/
PhyxObj2D::PhyxObj2D()
{
	xv = 0;
	yv = 0;
	xa = 0;
	ya = 0;
}//*/

void PhyxObj2D::Update(){
	auto tn = std::chrono::steady_clock::now();
	//if(t==NULL) t=tn;

	//double d = std::chrono::duration_cast<double, std::milli> d = tn - t;
	std::chrono::duration<float, std::milli> d = tn - t;
	float dd = d.count();
	t=tn;

	worldPosition += glm::vec3(v.x * (float)(dd/1000),0,v.y * (float)(dd/1000));
//	worldPosition.x += xv*dd/1000.;
//	worldPosition.z += yv*dd/1000.;

	v += a * (float)(dd/1000);
//	xv+=xa*dd/1000.;
//	yv+=ya*dd/1000.;
}

void PhyxObj2D::InitTime(){
	t = std::chrono::steady_clock::now();
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


void PhyxObj2D::AddForce(glm::vec2 _a) {
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