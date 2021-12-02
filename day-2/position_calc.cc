#include <iostream>
using namespace std;

// Time complexity: O(N)
// Space complexity: O(1)

int main()
{
	int x=0,y=0,sz;
	std::string d;

	while(cin >> d >> sz)
	{
		x += (d[0] == 'f') * sz;
		y += (d[0] == 'd') * sz;
		y -= (d[0] == 'u') * sz;
	}
	cout << x*y << endl;
}
