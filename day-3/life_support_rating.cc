#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

string step(auto startIt, auto endIt, bool keepMostCommon, int idx=0) // need -fconcepts
{
	if (startIt == prev(endIt))
		return *startIt;

	const auto it = partition(startIt, endIt, [idx](auto i){return i[idx]=='0';});
	const char mostCommon = (distance(startIt, it)*2 > distance(startIt, endIt)) ? '0':'1';
	return (keepMostCommon == (mostCommon == '0')) ?
			step(startIt, it, keepMostCommon, ++idx): step(it, endIt, keepMostCommon, ++idx);
}

int main()
{
	vector<string> input;
	string s;
	while(cin >> s)
		input.emplace_back(move(s));

	const auto& ogRatingStr = step(begin(input), end(input), true);
	const auto ogRating = strtoull(&ogRatingStr[0], NULL, 2);

	const auto& co2ScrubberRatingStr = step(begin(input), end(input), false);
	const auto co2ScrubberRating = strtoull(&co2ScrubberRatingStr[0], NULL, 2);
	
	cout << ogRating * co2ScrubberRating << endl;
}

