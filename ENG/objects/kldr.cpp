#include "kldr.h"

Collider::Collider(GameObj* p,int l){
	parent=p;
	layer=l;
}



bool CollisionENG::Collision(CircleCollider * A,CircleCollider * B){
	return (glm::distance(A->pos,B->pos) <= (A->dim+B->dim)); 
}

/*
CollisionMsg CircleCollider::collision(CircleCollider g){
	CollisionMsg out;
	out.nor = glm::normalize(g.pos-pos);
	out.tan = glm::vec2(out.nor.y*-1.,out.nor.x);
	out.overlap = (dim+g.dim)-glm::distance(pos,g.pos);
	return out;
}*/
/*
bool CircleCollider::isin(CircleCollider g){
	return (glm::distance(pos,g.pos) <= (dim+g.dim));
}

bool CircleCollider::isin(glm::dvec2 other){
	return (
		glm::distance(this->pos,other)
		<= this->dim);
}
*/
/*bool SphereCollider::boolin(glm::vec3 other){
	return (
		glm::distance(transform.pos,other)
		<= dim);
}*/
