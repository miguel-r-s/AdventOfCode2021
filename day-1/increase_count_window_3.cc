#include <iostream>
using namespace std;

// Rationale: we look only at the edges of the  sliding window, 
// since the middle is common to the two windows being compared.

// Time complexity: O(N)
// Space complexity: O(WindowSize) = O(1),
//    since Window Size is a constant
constexpr int WindowSize = 3;

int main()
{
	int n[WindowSize], counter=0;

	// Fill up the first window
	for (int i = 0; i < WindowSize; ++i)
	{
		cin >> n[i];
	}

	// Increase counter if the new value is higher
	// than the one it will replace
	for(int tmp, idx=0; cin >> tmp; idx=(idx+1)%WindowSize)
	{
		counter += (n[idx] < tmp);
		n[idx] = tmp;
	}
	cout << counter << '\n';
}
