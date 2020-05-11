#include "kldr.h"

CollisionMsg CircleCollider::collision(CircleCollider g){
	CollisionMsg out;
	out.dir = g.pos-pos;
	out.overlap = (dim+g.dim)-glm::distance(pos,g.pos);
	return out;
}

bool CircleCollider::boolin(CircleCollider g){
	return (glm::distance(pos,g.pos) <= (dim+g.dim));
}

bool CircleCollider::boolin(glm::vec2 other){
	return (
		glm::distance(this->pos,other)
		<= this->dim);
}

/*bool SphereCollider::boolin(glm::vec3 other){
	return (
		glm::distance(transform.pos,other)
		<= dim);
}*/