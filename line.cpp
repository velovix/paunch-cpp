#include "paunch.h"
#include "line.h"
#include "collision.h"
#include "point.h"

namespace paunch {

std::vector<Line> _getBoundingLines(Bounding bounding) {

	std::vector<Line> lines;

	lines.push_back(Line(Point(bounding.start.x, bounding.start.y), Point(bounding.end.x, bounding.start.y)));
	lines.push_back(Line(Point(bounding.end.x, bounding.start.y), Point(bounding.end.x, bounding.end.y)));
	lines.push_back(Line(Point(bounding.end.x, bounding.end.y), Point(bounding.start.x, bounding.end.y)));
	lines.push_back(Line(Point(bounding.start.x, bounding.end.y), Point(bounding.start.x, bounding.start.y)));

	return lines;
}

bool Line::Collides(Point &point) {

	return point.Collides(*this);
}

bool Line::Collides(Bounding &bounding) {

	return bounding.Collides(*this);
}

bool Line::Collides(Line &line) {

	if(!this->bounds.Collides(line.bounds)) {
		return false;
	}

	Point intersection = _getLineIntersection(*this, line);
	if(intersection.x != INFINITY && intersection.y != INFINITY) {
		return true;
	}

	return false;
}

bool Line::Collides(Polygon &polygon) {

	if(!this->bounds.Collides(polygon.bounds)) {
		return false;
	}

	for(unsigned int i=0; i<polygon.lines.size(); i++) {
		if(this->Collides(polygon.lines.at(i))) {
			return true;
		}
	}

	return false;
}

bool Line::Collides(Collider &collider) {

	return collider.Collides(*this);
}

Line::Line() {}

Line::Line(Point start, Point end) {

	Point calcStart, calcEnd;
	if(start.x > end.x) {
		calcStart = end;
		calcEnd = start;
	} else {
		calcStart = start;
		calcEnd = end;
	}

	this->start = calcStart;
	this->end = calcEnd;

	this->bounds = Bounding(this->start, this->end);

	this->slope = (this->end.y-this->start.y)/(this->end.x-this->start.x);
	this->yint = this->start.y - (this->slope * this->start.x);
}

Point Line::GetPointFromX(double x) {

	if(x < this->bounds.start.x) {
		return this->start;
	} else if(x > this->bounds.end.x) {
		return this->end;
	}

	if(this->slope == INFINITY || this->slope == -INFINITY) {
		return this->end;
	}

	return Point(x, (this->slope*x)+this->yint);
}

Point Line::GetPointFromY(double y) {

	if(y < this->bounds.start.y || y > this->bounds.end.y) {
		if(std::abs(this->start.y-y) < std::abs(this->end.y-y)) {
			return this->start;
		}

		return this->end;
	}

	if(this->slope == INFINITY || this->slope == -INFINITY) {
		return Point(this->start.x, y);
	}

	return Point((y-this->yint) / this->slope, y);
}

void Line::Move(double x, double y) {

	this->start.Move(x, y);
	this->end.Move(x, y);
	this->bounds.Move(x, y);

	this->yint = this->start.y - (this->slope * this->start.x);
}

void Line::SetPosition(double x, double y) {

	double xDisp = x - this->start.x;
	double yDisp = y - this->start.y;

	this->Move(xDisp, yDisp);
}

Double2 Line::GetPosition() {

	return Double2(this->start.x, this->start.y);
}

Double2 Line::DistanceToTangentPoint(Point &point, int side) {

	double x = point.x;
	double y = point.y;

	switch(side) {
	case Up:
		return _getPointDistance(point, this->GetPointFromX(x));
	case Down:
		return _getPointDistance(point, this->GetPointFromX(x));
	case Left:
		return _getPointDistance(point, this->GetPointFromY(y));
	case Right:
		return _getPointDistance(point, this->GetPointFromY(y));
	default:
		throw Error("Invalid side value");
	}
}

}
