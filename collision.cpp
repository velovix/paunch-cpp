#include "paunch.h"
#include "collision.h"

namespace paunch {

Point _getLineIntersection(Line &line1, Line &line2) {

	if(!line1.bounds.Collides(*((Collider*)&line2.bounds))) {
		return Point(INFINITY, INFINITY);
	}

	if(line1.slope == line2.slope) {
		return Point(INFINITY, INFINITY);
	}

	double line1A = line1.end.y - line1.start.y;
	double line1B = line1.start.x - line1.end.x;
	double line1C = line1A*line1.start.x + line1B*line1.start.y;

	double line2A = line2.end.y - line2.start.y;
	double line2B = line2.start.x - line2.end.x;
	double line2C = line2A*line2.start.x + line2B*line2.start.y;

	double determinate = line1A*line2B - line2A*line1B;

	double x = (line2B*line1C-line1B*line2C) / determinate;
	double y = (line1A*line2C-line2A*line1C) / determinate;

	if(x >= line1.start.x && x <= line1.end.x && y >= line1.start.y && y <= line1.end.y) {
		return Point(x, y);
	}

	return Point(INFINITY, INFINITY);
}

}
