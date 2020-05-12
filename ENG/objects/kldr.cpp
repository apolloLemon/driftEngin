#include "kldr.h"

CollisionMsg CircleCollider::collision(CircleCollider g){
	CollisionMsg out;
	out.dir = g.pos-pos;
	out.overlap = (dim+g.dim)-glm::distance(pos,g.pos);
	return out;
}

bool CircleCollider::isin(CircleCollider g){
	return (glm::distance(pos,g.pos) <= (dim+g.dim));
}

bool CircleCollider::isin(glm::dvec2 other){
	return (
		glm::distance(this->pos,other)
		<= this->dim);
}

/*bool SphereCollider::boolin(glm::vec3 other){
	return (
		glm::distance(transform.pos,other)
		<= dim);
}*/