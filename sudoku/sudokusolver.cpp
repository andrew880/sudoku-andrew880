// sudoku.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "sudokusolver.h"

int main() {
	SudokuBoard board;
	std::cin >> board;
}

SudokuSolver::SudokuSolver() {

}

SudokuSolver::SudokuSolver(std::string board_string)
{
	board = SudokuBoard::SudokuBoard(board_string);
}

SudokuSolver::SudokuSolver(SudokuBoard sudoku_board)
{
	board = sudoku_board;
}

bool SudokuSolver::checkSolved()
{
	bool solved = true;
	for (int i = 0; i < kBoardSize * kBoardSize; i++) {
		if (!board.IsSolved(i)) {
			solved = false;
		}
	}
	return solved;
}

SudokuBoard SudokuSolver::GetSolved()
{
	EliminatePossibilities();
	return board;
}

SudokuBoard SudokuSolver::GetBoard()
{
	return board;
}

void SudokuSolver::EliminatePossibilities()
{
	while (!checkSolved()) {
		for (int i = 0; i < kBoardSize * kBoardSize; i++) {
			if (board.IsSolved(i)) {
				EliminateSameBox(i);
				EliminateSameLine(i);
			}
		}
	}
}

void SudokuSolver::EliminateSameBox(int index)
{
	int startcol = (index % kBoardSize) - (index % kBoardSize) % kBoxSize; //starting col
	for (unsigned int i = startcol; i < (startcol + kBoxSize); i++) { //go through col of box
		int startrow = (index / kBoardSize) - (index / kBoardSize) % kBoxSize; //starting row
		for (unsigned int j = startrow; j < (startrow + kBoxSize); j++) {//go through row of box
			if (!board.IsSolved(i + j * kBoardSize) && (i + j * kBoardSize) != index) {
				board.EliminatePossibility(i + j * kBoardSize, board.GetPossibilities(index).at(0));
			}
		}
	}
}

void SudokuSolver::EliminateSameLine(int index)
{
	int j = (index / kBoardSize) * kBoardSize; //row
	for (unsigned int i = j; i < (j + kBoardSize); i++) {
		if (!board.IsSolved(i) && i != index) {
			board.EliminatePossibility(i, board.GetPossibilities(index).at(0));
		}
	}
	int i = (index % kBoardSize);
	for (unsigned int j = i; j < kBoardSize * kBoardSize; j += kBoardSize) {//col
		if (!board.IsSolved(j) && j != index) {
			board.EliminatePossibility(j, board.GetPossibilities(index).at(0));
		}
	}
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file