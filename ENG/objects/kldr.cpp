#include "kldr.h"

bool CircleCollider::boolin(glm::vec2 other){
	return (
		glm::distance(worldpos+transform.pos,other)
		<=
		radius
		)
}