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
	a+=_a;
}
/*/
void PhyxObj2D::AddForce(double _x, double _y) {
	xa += _x;
	ya += _y;
}
//*/



