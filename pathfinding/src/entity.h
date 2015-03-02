//  Entity Class Definition
// Maintains a collection of Entity properties.
//
//  Mobile Entity Class Defintion
// Extends Entity class.
// Maintains a collection of MobileEntity properties.
// Invokes pathfinding when it has a task.
//

#ifndef ENTITY_H_
#define ENTITY_H_

#include <string>
#include <vector>
#include "position.h"
#include "PathMemory.h"

class Entity 
{
protected:
	Position position;

public:
	Entity(Position);
	Entity(const Entity&);
	Entity();

	Entity& operator= (const Entity&);

	Position getPosition() const;

	void setPosition(Position);

	friend std::ostream& operator<< (std::ostream & os, const Entity & entity)
	{
		os << entity.position;
		return os;
	}
};

class MobileEntity : public Entity, public PathMemory
{
private:
	double sightRange;
	Entity * target;

public:
	MobileEntity();
	MobileEntity(const Entity&);
	double getSightRange();
	Entity* getTarget();
	void setSightRange(double);
	void setTarget(Entity*);
};

#endif

typedef MobileEntity Human;