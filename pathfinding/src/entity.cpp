//  Entity Class Implementation
//  Mobile Entity Class Implementation
//

#include "entity.h"
#include "pathfinding.h"

Entity::Entity(Position position) :
	position(position)
{ }

Entity::Entity(const Entity & entity) :
	position(entity.position)
{ }

Entity::Entity() :
	position()
{ }

Entity& Entity::operator= (const Entity& entity)
{
	position = entity.position;
	return *this;
}

Position Entity::getPosition() const
{
	return this->position;
}

void Entity::setPosition(Position position)
{
	this->position = position;
}

////////
//  MOBILE ENTITY
////////

MobileEntity::MobileEntity() :
	Entity(),
	target(0),
	PathMemory()
{}

MobileEntity::MobileEntity(const Entity & entity) :
	Entity(entity),
	target(0),
	PathMemory()
{}

double MobileEntity::getSightRange()
{
	return this->sightRange;
}

Entity* MobileEntity::getTarget() 
{
	return this->target;
}

void MobileEntity::setSightRange(double range) 
{
	this->sightRange = range;
}

void MobileEntity::setTarget(Entity* target) 
{
	this->target = target;
}
