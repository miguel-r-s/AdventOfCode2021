#include <iostream>
#include <vector>
#include <array>
#include <tuple>
using namespace std;

struct Idx    { int mIdx, mRowIdx, mColIdx; };
struct Scores { int mSum{}, mRowScore[5]{}, mColScore[5]{}; bool mHasWon=false; };

vector<int> parse_numbers()
{
	vector<int> numbers;
	int n; char c;
	while(cin >> n >> c and c == ',')
		numbers.push_back(n);
	return numbers;
}

auto parse_boards()
{
	array<vector<Idx>,100> boardsPerNumber;
	vector<Scores> boardScores;
	int n, cnt=0;
	while(cin >> n)
	{
		const int boardNum = cnt/25;
		boardsPerNumber[n].push_back(Idx{boardNum,cnt/5-5*boardNum,cnt%5});
		boardScores.resize(boardNum+1);
		boardScores[boardNum].mSum += n;
		++cnt;
	}
	return make_tuple(boardsPerNumber, boardScores);
}

int find_winner_score(const auto& numbers, auto& boardsPerNumber, auto& boardScores)
{
	for (auto n : numbers)
	{
		for (auto& board : boardsPerNumber[n])
		{
			const int idx = board.mIdx,
				  row = board.mRowIdx,
				  col = board.mColIdx;
			boardScores[idx].mSum -= n;
			boardScores[idx].mRowScore[row]++;
			boardScores[idx].mColScore[col]++;
			if (boardScores[idx].mRowScore[row] == 5 or
				boardScores[idx].mColScore[col] == 5)
			{
				return boardScores[idx].mSum * n;
			}
		}
	}
	return -1;
}

int find_loser_score(const auto& numbers, auto& boardsPerNumber, auto& boardScores)
{
	int numWinners = 0;
	for (auto n : numbers)
	{
		for (auto& board : boardsPerNumber[n])
		{
			const int idx = board.mIdx,
				  row = board.mRowIdx,
				  col = board.mColIdx;
			boardScores[idx].mSum -= n;
			boardScores[idx].mRowScore[row]++;
			boardScores[idx].mColScore[col]++;
			if (not boardScores[idx].mHasWon and
				(boardScores[idx].mRowScore[row] == 5 or
				 boardScores[idx].mColScore[col] == 5))
			{
				boardScores[idx].mHasWon = true;
				if (++numWinners == boardScores.size())
				{
					return boardScores[idx].mSum * n;
				}
			}
		}
	}
	return -1;
}

void usage() { cout << "usage: ./bingo (winner|loser)\n"; }

int main(int argc, char** argv)
{
	const auto numbers = parse_numbers();
	auto&& [boardsPerNumber, boardScores] =  parse_boards();
	if (argc != 2)
	{
		usage();
		return -1;
	}

	if ("winner" == string(argv[1]))
		cout << find_winner_score(numbers, boardsPerNumber, boardScores) << endl;
	else if ("loser" == string(argv[1]))
		cout << find_loser_score(numbers, boardsPerNumber, boardScores) << endl;
	else
		usage();
}
