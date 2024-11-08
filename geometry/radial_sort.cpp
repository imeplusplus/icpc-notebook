#include "basics.cpp"

/*
	below < above
	order: [pi, 2 * pi)

	Example:
	[(1, 0), (1, 1), (0, 1), (-1, 0), (-1, -1), (0, -1)]
		after sort =>
	[(-1, 0), (-1, -1), (0, -1), (1, 0), (1, 1), (0, 1)]
*/

// Don't forget to change origin!
point origin;

int above(point p){
	if(p.y == origin.y) return p.x > origin.x;
	return p.y > origin.y;
}

bool cmp(point p, point q){
	int tmp = above(q) - above(p);
	if(tmp) return tmp > 0;

	return p.dir(origin,q) > 0;
	//Be Careful: p.dir(origin,q) == 0
}