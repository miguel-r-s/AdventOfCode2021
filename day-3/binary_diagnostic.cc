#include <iostream>
using namespace std;

int main()
{
	constexpr int Size = 12;
	unsigned int a[Size] = {0};
	int n = 0;
	string s;
	while(cin >> s)
	{
		for (int i = 0; i < Size; ++i)
		{
			a[i] += (s[i] == '1');
		}
		++n;
	}

	unsigned int gamma = 0;
	for (int i = 0; i < Size; ++i)
	{
		gamma |= ((a[i]<<1>n) << (Size-i-1)); // golf!
	}

	const int bitmask = (1<<Size)-1;
	cout << gamma * (bitmask&~gamma) << endl;
}
