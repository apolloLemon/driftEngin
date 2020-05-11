#include "kldr.h"

bool CircleCollider::boolin(glm::vec2 other){
	return (
		glm::distance(worldpos+transform.pos,other)
		<=
		dim
		)
}

bool SphereCollider::boolin(glm::vec3 other){
	return (
		glm::distance(worldpos+transform.pos,other)
		<=
		dim
		)
}