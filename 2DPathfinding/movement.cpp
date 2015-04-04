#include "Movement.h"

void Movement::moveMobileEntity(MobileEntity* entity, ObstructionMap* obsMap)
{
	Position currentPos = entity->getPosition();
	Position newPos;

	if (entity->getTarget())
	{
		Position nextPos = Movement::moveTowardsTarget(entity, obsMap);
		Position targetPos = entity->getTarget()->getPosition();
		newPos = entity->moveOnPath(currentPos, nextPos, targetPos);

		if (!entity->onPath())
			entity->setTarget(NULL);
	}

	if (!obsMap->isConsidered(newPos))
	{
		obsMap->set(currentPos, OT_EMPTY);
		entity->setPosition(newPos);
		obsMap->set(newPos, OT_CONSIDERED);
	}
}

double Movement::evaluateScore(MobileEntity* entity, Position nextPos, ObstructionMap* obsMap)
{
	double score = 0;
	Position pos = entity->getPosition();
	Position target = entity->getTarget()->getPosition();
	
	switch (entity->pathMap.get(nextPos))
	{
	case PathMemory::PathMapState::VISITED:
		score -= 4;
		break;
	case PathMemory::PathMapState::UNKNOWN:
		score += 2;
		break;
	case PathMemory::PathMapState::OBSERVED:
		score += 1;
		break;
	}
	score += EuclideanDistance(pos, target) - EuclideanDistance(nextPos, target);
	return score;
}

Position Movement::moveTowardsTarget(MobileEntity* entity, ObstructionMap* obsMap)
{
	double bestScore = -inf;
	double score = 0;
	Direction bestDir = D_NONE;
	Position start = entity->getPosition();
	Position neighbor;

	for (int dir = D_NORTH; dir < D_COUNT; dir++)
	{
		neighbor = start.getNeighbor(dir);
		if (obsMap->isOpen(neighbor) && neighbor.checkSanity())
		{
			score = evaluateScore(entity, neighbor, obsMap);
			if (score > bestScore)
			{
				bestScore = score;
				bestDir = dir;
			}
		}
	}
	return start.getNeighbor(bestDir);
}

Position Movement::moveAwayFromTarget(MobileEntity* entity, ObstructionMap* obsMap)
{
	double bestScore = inf;
	double score = 0;
	Direction bestDir = D_NONE;
	Position start = entity->getPosition();
	Position neighbor;

	for (int dir = D_NORTH; dir < D_COUNT; dir++)
	{
		neighbor = start.getNeighbor(dir);
		if (obsMap->isOpen(neighbor) && neighbor.checkSanity())
		{
			score = evaluateScore(entity, neighbor, obsMap);
			if (score < bestScore)
			{
				bestScore = score;
				bestDir = dir;
			}
		}
	}
	return start.getNeighbor(bestDir);
}
