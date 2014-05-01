#include "paunch.h"
#include "point.h"
#include "collision.h"

namespace paunch {

Double2 _getPointDistance(Point point1, Point point2) {

	return Double2(point2.x-point1.x, point2.y-point1.y);
}

bool Point::Collides(Point &point) {

	if(this->x == point.x && this->y == point.y) {
		return true;
	}

	return false;
}

bool Point::Collides(Bounding &bounding) {

	if(this->x >= bounding.start.x && this->x <= bounding.end.x &&
		this->y >= bounding.start.y && this->y <= bounding.end.y) {
		return true;
	}

	return false;
}

bool Point::Collides(Line &line) {

	if(line.slope == INFINITY) {
		if(this->y >= line.bounds.start.y && this->y <= line.bounds.end.y && std::abs(this->x-line.start.x) < tolerance) {
			return true;
		}

		return false;
	}

	if(!this->Collides(line.bounds)) {
		return false;
	}

	if(std::abs(this->y-((line.slope*this->x)+line.yint)) < tolerance) {
		return true;
	}

	return false;
}

bool Point::Collides(Polygon &polygon) {

	if(!this->Collides(polygon.bounds)) {
		return false;
	}

	Line ray = Line(Point(std::floor(this->x), std::floor(this->y)),
		Point(std::floor(this->x+(polygon.bounds.end.x-polygon.bounds.start.x)), std::floor(this->y)));

	int intersects = 0;
	for(auto &val: polygon.lines) {
		Point intersectPnt = _getLineIntersection(ray, val);
		if(intersectPnt.x == INFINITY && intersectPnt.y == INFINITY) {
			continue;
		} else {
			bool isOnVertex = false;
			if(intersectPnt.Collides(val.start) && val.end.y < intersectPnt.y) {
				intersects++;
				isOnVertex = true;
			} else if(intersectPnt.Collides(val.end) && val.start.y < intersectPnt.y) {
				intersects++;
				isOnVertex = true;
			} else if(intersectPnt.Collides(val.end) || intersectPnt.Collides(val.start)) {
				isOnVertex = true;
			}

			if(!isOnVertex) {
				intersects++;
			}
		}
	}

	if(intersects%2 == 0) {
		return false;
	}

	return true;
}

bool Point::Collides(Collider &collider) {

	return collider.Collides(*this);
}

Point::Point() {

	this->x = 0;
	this->y = 0;
}

Point::Point(double x, double y) {

	this->x = x;
	this->y = y;
}

void Point::Move(double x, double y) {

	this->x += x;
	this->y += y;
}

void Point::SetPosition(double x, double y) {

	double xDisp = x - this->x;
	double yDisp = y - this->y;

	this->Move(xDisp, yDisp);
}

Double2 Point::GetPosition() {

	return Double2(this->x, this->y);
}

Double2 Point::DistanceToTangentPoint(Point &point, int side) {

	return _getPointDistance(*this, point);
}

}
