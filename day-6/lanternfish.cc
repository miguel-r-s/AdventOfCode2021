#include <vector>
#include <numeric>
#include <iostream>
#include <boost/circular_buffer.hpp>
using namespace std;

using buffer = boost::circular_buffer<unsigned long int>;

buffer::value_type num_fish(const auto& lanternfish)
{
	buffer::value_type n = 0;
	for (int i=0; i < lanternfish.size(); ++i)
	{
		n+=lanternfish[i];
	}
	return n;
}

void reproduce(buffer lanternfish, int generations)
{

	cout << "Computing number of lanternfish after " << generations << " generations: ";
	while (generations--)
	{
		const auto n_reproducers = lanternfish[0];
		lanternfish.push_back(n_reproducers); // new ones
		lanternfish[6] += n_reproducers; // ones that just gave birth
	}
	cout << num_fish(lanternfish) << '\n';
}

auto parse_input()
{
	buffer a(9,0);
	int n; char _;
	while(cin >> n)
	{
		++a[n];
		cin >> _; // ignore
	}
	return a;
}

int main()
{
	auto lanternfish = parse_input();

	reproduce(lanternfish, 80);
	reproduce(lanternfish, 256);
}
