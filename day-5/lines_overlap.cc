#include <unordered_map>
#include <vector>
#include <boost/functional/hash.hpp>
#include <iostream>
using namespace std;

struct  Point
{
	Point(int x, int y) : x(x), y(y) {}

	bool operator==(const Point& p) const 
	{
		return x == p.x and y == p.y;
	}

	int x=0, y=0;
};

namespace std
{
template <> struct hash<Point>
{
	std::size_t operator()(const Point& p) const
	{
		std::size_t result = 0;
		boost::hash_combine(result, p.x);
		boost::hash_combine(result, p.y);
		return result;
	}
};
}

int sign(int x) { return (x > 0) - (x < 0); }

struct Line
{
	Line(Point p1, Point p2) : p1(p1), p2(p2) { }

	vector<Point> points() const
	{
		const int deltaX = sign(p2.x-p1.x);
		const int deltaY = sign(p2.y-p1.y);

		vector<Point> pts;
		for (int x = p1.x, y = p1.y;
			not (x == p2.x+deltaX and y == p2.y+deltaY);
			x += deltaX, y += deltaY)
			pts.emplace_back(x,y);
		return pts;
	}

	Point p1, p2;
};

int count_intersections(bool keepDiagonals)
{
	int x1,y1,x2,y2;
	int cnt {0};
	unordered_map<Point, int> pointCount;
	while(scanf("%d,%d -> %d,%d", &x1, &y1, &x2, &y2)!=EOF)
	{
		if (not keepDiagonals and (x1 != x2 and y1 != y2))
			continue;

		const auto& line = Line{Point{x1,y1}, Point{x2,y2}};
		for (const auto& p : line.points())
		{
			cnt += (++pointCount[p] == 2);
		}
	}
	return cnt;
}

int main()
{
	// false: first challenge (discard diagonals)
	// true: second challenge (keep diagonals)
	cout << count_intersections(false) << '\n';
}
