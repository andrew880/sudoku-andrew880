#ifndef SUDOKUSOLVER_H
#define SUDOLUSOLVER_H

#include <iostream>
#include "sudokuboard.h"

class SudokuSolver {
	private:
		static const int kBoardSize = 9;
		static const int kBoxSize = 3;

		SudokuBoard board;

	public:
		SudokuSolver();
		SudokuSolver(std::string board_string);
		SudokuSolver(SudokuBoard sudoku_board);

		bool checkSolved();

		SudokuBoard GetSolved();
		SudokuBoard GetBoard();

		void EliminatePossibilities();

		void EliminateSameBox(int index);

		void EliminateSameLine(int index);
};

#endif // !SUDOKUSOLVER_H