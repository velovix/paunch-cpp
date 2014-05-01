#include "paunch.h"
#include "point.h"

namespace paunch {

bool Polygon::Collides(Point &point) {

	return point.Collides(*this);
}

bool Polygon::Collides(Bounding &bounding) {

	return bounding.Collides(*this);
}

bool Polygon::Collides(Line &line) {

	return line.Collides(*this);
}

bool Polygon::Collides(Polygon &polygon) {

	if(!this->bounds.Collides(polygon.bounds)) {
		return false;
	}

	for(unsigned int i=0; i<this->lines.size(); i++) {
		if(polygon.Collides(this->lines.at(i))) {
			return true;
		}
	}

	return false;
}

bool Polygon::Collides(Collider &collider) {

	return collider.Collides(*this);
}

Polygon::Polygon() {}

Polygon::Polygon(std::vector<Point> points) {

	Point min = Point(INFINITY, INFINITY);
	Point max = Point(-INFINITY, -INFINITY);

	for(unsigned int i=0; i<points.size(); i++) {
		if(i < points.size()-1) {
			this->lines.push_back(Line(points.at(i), points.at(i+1)));
		} else {
			this->lines.push_back(Line(points.at(i), points.at(0)));
		}

		if(points.at(i).x > max.x) {
			max.x = points.at(i).x;
		}
		if(points.at(i).y > max.y) {
			max.y = points.at(i).y;
		}
		if(points.at(i).x < min.x) {
			min.x = points.at(i).x;
		}
		if(points.at(i).y < min.y) {
			min.y = points.at(i).y;
		}
	}

	this->bounds = Bounding(min, max);
}

void Polygon::Move(double x, double y) {

	for(unsigned int i=0; i<this->lines.size(); i++) {
		this->lines[i].Move(x, y);
	}

	this->bounds.Move(x, y);
}

void Polygon::SetPosition(double x, double y) {

	double xDisp = x - this->lines[0].start.x;
	double yDisp = y - this->lines[0].start.y;

	this->Move(xDisp, yDisp);
}

Double2 Polygon::GetPosition() {

	return Double2(this->lines.at(0).start.x, this->lines.at(0).start.y);
}

Double2 Polygon::DistanceToTangentPoint(Point &point, int side) {

	switch(side) {
	case Up: {
		Point top(point.x, -INFINITY);
		for(auto &val: this->lines) {
			Point linePnt = val.GetPointFromX(point.x);
			if(linePnt.y > top.y && point.x >= val.start.x && point.x <= val.end.x) {
				top = linePnt;
			}
		}

		if(top.y != INFINITY && top.y != -INFINITY) {
			return _getPointDistance(point, top);
		}

		for(auto &val: this->lines) {
			Point linePnt = val.GetPointFromX(point.x);
			if(linePnt.y > top.y) {
				top = linePnt;
			}
		}
		return _getPointDistance(point, top);
	}
	case Down: {
		Point bottom(point.x, INFINITY);
		for(auto &val: this->lines) {
			Point linePnt = val.GetPointFromX(point.x);
			if(linePnt.y < bottom.y && point.x >= val.start.x && point.x <= val.end.x) {
				bottom = linePnt;
			}
		}

		if(bottom.y != INFINITY && bottom.y != -INFINITY) {
			return _getPointDistance(point, bottom);
		}

		for(auto &val: this->lines) {
			Point linePnt = val.GetPointFromX(point.x);
			if(linePnt.y > bottom.y) {
				bottom = linePnt;
			}
		}
		return _getPointDistance(point, bottom);
	}
	case Left: {
		Point left(INFINITY, point.y);
		for(auto &val: this->lines) {
			Point linePnt = val.GetPointFromY(point.y);
			if(linePnt.x < left.x && point.y >= val.start.y && point.y <= val.end.y) {
				left = linePnt;
			}
		}

		if(left.x != INFINITY && left.x != -INFINITY) {
			return _getPointDistance(point, left);
		}

		for(auto &val: this->lines) {
			Point linePnt = val.GetPointFromY(point.y);
			if(linePnt.x < left.x) {
				left = linePnt;
			}
		}
		return _getPointDistance(point, left);
	}
	case Right: {
		Point right(-INFINITY, point.y);
		for(auto &val: this->lines) {
			Point linePnt = val.GetPointFromY(point.y);
			if(linePnt.x > right.x && point.y >= val.start.y && point.y <= val.end.y) {
				right = linePnt;
			}
		}

		if(right.x != INFINITY && right.x != -INFINITY) {
			return _getPointDistance(point, right);
		}

		for(auto &val: this->lines) {
			Point linePnt = val.GetPointFromY(point.y);
			if(linePnt.x > right.x) {
				right = linePnt;
			}
		}
		return _getPointDistance(point, right);
	}
	default:
		throw Error("Invalid side value");
	}
}

}
