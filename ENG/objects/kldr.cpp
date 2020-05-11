#include "kldr.h"

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