#include "sudokuboard.h"
#include "sudokusolver.h"
#include <fstream>
#include <iostream>
#include <string>

SudokuBoard::SudokuBoard()
{
}

SudokuBoard::SudokuBoard(std::string board_string) {
	for (unsigned int i = 0; i < board_string.length(); i++)
	{
		if (board_string.at(i) == '_')
		{
			int sample[] = { '1','2','3','4','5','6','7','8','9' };
			std::vector<int> pool(sample, sample + sizeof(sample) / sizeof(int));
			boardTile unsolved_tile{ false, pool };
			board.push_back(unsolved_tile);
		}
		else {
			std::vector<int> solution;
			solution.push_back(board_string.at(i));
			boardTile solved_tile{ true, solution };
			board.push_back(solved_tile);
		}
	}
}

void SudokuBoard:: SetView(bool should_view) {
	view_result = should_view;
}

bool SudokuBoard::IsSolved(int i)
{
	return board.at(i).solved;
}

std::vector<int> SudokuBoard::GetPossibilities(int i)
{
	return board.at(i).pool;
}

void SudokuBoard::EliminatePossibility(int position, int possibility)
{
	if (!board.at(position).solved) {
		for (int i = 0; i < board.at(position).pool.size(); i++) {
			if (board.at(position).pool.at(i) == possibility) {
				(board.at(position).pool).erase(board.at(position).pool.begin() + i);
			}
		}
		if (board.at(position).pool.size() == 1) {
			board.at(position).solved = true;
		}
	}
}

std::ostream & operator<<(std::ostream & out, SudokuBoard & board)
{
	string str = "";
	for (int i = 0; i < board.board.size(); i++) {
		if (i % 9 == 0 && i != 0) {
			str += '\n';
		}
		if (!board.IsSolved(i)) {
			str += '_';
		}
		if (board.IsSolved(i)) {
			str += (char)board.GetPossibilities(i).at(0);
		}
	}
	str += "\n\n";
	if (board.view_result) {
		out << "Solution:\n" << str;
	}
	else {
		std::cout << "stored\n";
		std::ifstream readfile("result.txt");
		if (readfile.is_open())
		{
			string line;
			while (std::getline(readfile, line))
			{
				str += line + "\n";
			}
		}
		std::ofstream writefile("result.txt");
		if (writefile.is_open())
		{
			writefile << str;
			writefile.close();
		}
		else std::cout << "Unable to open file";
	}
	return out;
}

static bool ShouldViewResult() {
	char view;
	std::cout << "[Y] to view results, otherwise it will be saved to results.txt\n";
	std::cin >> view;
	return (view == 'Y' || view == 'y');
}

std::istream & operator>>(std::istream & in, SudokuBoard & board)
{
	char* file_name = new char[20];
	bool should_view_result = ShouldViewResult();
	std::cout << "Enter File Name of Sudoku puzzles:";
	std::cin >> file_name;
	std::ifstream myfile(file_name);

	if (myfile.is_open())
	{
		string line;
		while (std::getline(myfile, line))
		{
			std::cout << "\nInput:\n" << line << "\n";
			board = SudokuBoard(line);
			SudokuSolver solver = SudokuSolver(line);
			SudokuBoard solved = solver.GetSolved();
			solved.SetView(should_view_result);
			std::cout << solved;
		}
		myfile.close();
	}
	else std::cout << "Unable to open file";

	delete file_name;
	return in;
}
