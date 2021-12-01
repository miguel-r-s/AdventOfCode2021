#include <iostream>
using namespace std;

// Time complexity: O(N)
// Space complexity: O(1)

int main()
{
	int n1, n2, counter=0;
	cin >> n1;
	while(cin >> n2)
	{
		counter += (n1 < n2);
		n1 = n2;
	}
	cout << counter << '\n';
}
