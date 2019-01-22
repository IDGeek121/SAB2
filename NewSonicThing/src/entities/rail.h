#ifndef RAIL_H
#define RAIL_H

#include <vector>
#include "entity.h"
#include "../toolbox/vector.h"

class RailSegment
{
public:
	int index; //Our index in the rails vector
	std::vector<RailSegment>* rails;
	Vector3f pointBegin;
	Vector3f pointEnd;
	Vector3f pointsDiff;
	//Vector3f velToAdd; //vel to add to the player due to gravity
	float speedToAdd; //speed to add to players vel. 
	float length;
	bool playerIsOn;
	float playerProgress; //players progress through the rail. 0 = at the begin point, 0.5 = halfway inbetween, 1 = at the end

	RailSegment(Vector3f* begin, Vector3f* end, std::vector<RailSegment>* rails, int index);

	//returns distance to closest point on line segment
	float distanceToPoint(Vector3f* point);

	//returns closest point on this line segment to the given point
	Vector3f closestPoint(Vector3f* point);

	//given a point, calculate how far along the given point is along the segment, 0 being near the begin, 1 being at the end
	float calcProgress(Vector3f* point);
};

class Rail : public Entity
{
private:
	//std::vector<Vector3f> pointsList;
	std::vector<RailSegment> rails;
	RailSegment* currentSegment;
	int currentSegmentIndex;
	float playerSpeed; //positive speed means going to end point from start point
	float timer;
	float minX;
	float minY;
	float minZ;
	float maxX;
	float maxY;
	float maxZ;

public:
	Rail(const char* railPath);

	void step();
};
#endif