#include "paunch.h"
#include "line.h"
#include "point.h"

namespace paunch {

bool Bounding::Collides(Point &point) {

	return point.Collides(*this);
}

bool Bounding::Collides(Bounding &bounding) {

	if(this->start.x > bounding.end.x || this->end.x < bounding.start.x ||
		this->start.y > bounding.end.y || this->end.y < bounding.start.y) {
		return false;
	}

	return true;
}

bool Bounding::Collides(Line &line) {

	if(!this->Collides(line.bounds)) {
		return false;
	}

	if(this->Collides(line.start) || this->Collides(line.end)) {
		return true;
	}

	std::vector<Line> boundLines = _getBoundingLines(*this);
	for(unsigned int i=0; i<boundLines.size(); i++) {
		if(boundLines.at(i).Collides(line)) {
			return true;
		}
	}

	return false;
}

bool Bounding::Collides(Polygon &polygon) {

	if(!this->Collides(polygon.bounds)) {
		return false;
	}

	if(this->start.Collides(polygon) || this->end.Collides(polygon) ||
		Point(this->start.x, this->end.y).Collides(polygon) ||
		Point(this->end.x, this->start.y).Collides(polygon)) {
		return true;
	}

	std::vector<Line> boundLines = _getBoundingLines(*this);
	for(unsigned int i=0; i<boundLines.size(); i++) {
		if(boundLines.at(i).Collides(polygon)) {
			return true;
		}
	}

	return false;
}

bool Bounding::Collides(Collider &collider) {

	return collider.Collides(*this);
}

Bounding::Bounding() {}

Bounding::Bounding(Point start, Point end) {

	Point checkStart, checkEnd;
	if(start.x >= end.x) {
		checkEnd.x = start.x;
		checkStart.x = end.x;
	} else {
		checkEnd.x = end.x;
		checkStart.x = start.x;
	}
	if(start.y >= end.y) {
		checkEnd.y = start.y;
		checkStart.y = end.y;
	} else {
		checkEnd.y = end.y;
		checkStart.y = start.y;
	}

	this->start = checkStart;
	this->end = checkEnd;
}

void Bounding::Move(double x, double y) {

	this->start.Move(x,y);
	this->end.Move(x,y);
}

void Bounding::SetPosition(double x, double y) {

	double width = this->end.x - this->start.x;
	double height = this->end.y - this->start.y;

	this->start = Point(x, y);
	this->end = Point(x+width, y+height);
}

Double2 Bounding::GetPosition() {

	return Double2(this->start.x, this->start.y);
}

Double2 Bounding::DistanceToTangentPoint(Point &point, int side) {

	double x = point.x;
	double y = point.y;

	switch(side) {
	case Up:
		if(point.x < this->start.x) {
			x = this->start.x;
		} else if(point.x > this->end.x) {
			x = this->end.x;
		}
		return _getPointDistance(point, Point(x, this->end.y));
	case Down:
		if(point.x < this->start.x) {
			x = this->start.x;
		} else if(point.x > this->end.x) {
			x = this->end.x;
		}
		return _getPointDistance(point, Point(x, this->start.y));
	case Left:
		if(point.y < this->start.y) {
			y = this->start.y;
		} else if(point.y > this->end.y) {
			y = this->end.y;
		}
		return _getPointDistance(point, Point(this->start.x, y));
	case Right:
		if(point.y < this->start.y) {
			y = this->start.y;
		} else if(point.y > this->end.y) {
			y = this->end.y;
		}
		return _getPointDistance(point, Point(this->end.x, y));
	default:
		throw Error("Invalid side value");
	}
}

}
