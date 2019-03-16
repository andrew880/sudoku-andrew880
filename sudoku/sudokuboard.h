#ifndef SUDOKUBOARD_H
#define SUDOKUBOARD_H

#include <iostream>
#include <vector>
#include <ostream>
#include <istream>
#include <fstream>

using std::string;

class SudokuBoard {
	private:
		struct boardTile {
			bool solved;
			std::vector<int> pool;
		};
	
		static const int kBoardSize = 9;
		
		bool view_result;
		std::vector<boardTile> board;

	public:
		SudokuBoard();
		SudokuBoard(string board_string);

		void SetView(bool should_view);

		bool IsSolved(int i);

		std::vector<int> GetPossibilities(int i);

		void EliminatePossibility(int position, int possibility);

		friend std::ostream & operator << (std::ostream &out, SudokuBoard &board);
		friend std::istream & operator >> (std::istream &in, SudokuBoard &board);
};
#endif // SUDOKUBOARD_H