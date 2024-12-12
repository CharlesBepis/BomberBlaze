#include "Collisions.h"

sfBool IsCollidingRectangleRectangle(sfVector2f _rect1, sfVector2f _rect2, sfVector2u _size1, sfVector2u _size2)
{
	return ((_rect1.x + _size1.x > _rect2.x) && (_rect1.x < _rect2.x + _size2.x) && (_rect1.y + _size1.y > _rect2.y) && (_rect1.y < _rect2.y + _size2.y));
}