#include <assert.h>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "sudokuboard.h"
#include "sudokusolver.h"

string puzzle = "___8_5____3__6___7_9___38___4795_3______71_9____2__5__1____248___9____5______6___\n";

TEST_CASE("sudokuboard GetPossiblities test") {
	SECTION("get all possiblities") {
		SudokuBoard board = SudokuBoard(puzzle);
		REQUIRE((int) board.GetPossibilities(0).size() == 9);
	}
	SECTION("get one possiblity") {
		SudokuBoard board = SudokuBoard(puzzle);
		REQUIRE((int) board.GetPossibilities(3).size() == 1);
	}
}
TEST_CASE("sudokuboard EliminatePossibility test") {
	SECTION("Eliminate one possibility") {
		SudokuBoard board = SudokuBoard(puzzle);
		board.EliminatePossibility(0, '1');
		REQUIRE((int) board.GetPossibilities(0).size() == 8);
	}
	SECTION("Eliminate all but one possibility") {
		SudokuBoard board = SudokuBoard(puzzle);
		board.EliminatePossibility(0, '1');
		board.EliminatePossibility(0, '2');
		board.EliminatePossibility(0, '3');
		board.EliminatePossibility(0, '4');
		board.EliminatePossibility(0, '5');
		board.EliminatePossibility(0, '6');
		board.EliminatePossibility(0, '7');
		board.EliminatePossibility(0, '8');
		REQUIRE((int)board.GetPossibilities(0).size() == 1);
	}
}
TEST_CASE("sudokuboard IsSolved test") {
	SECTION("not solved") {
		SudokuBoard board = SudokuBoard(puzzle);
		REQUIRE(board.IsSolved(0) == false);
	}
	SECTION("initially solved") {
		SudokuBoard board = SudokuBoard(puzzle);
		REQUIRE(board.IsSolved(3) == true);
	}
	SECTION("solved with elimination") {
		SudokuBoard board = SudokuBoard(puzzle);
		board.EliminatePossibility(0, '1');
		board.EliminatePossibility(0, '2');
		board.EliminatePossibility(0, '3');
		board.EliminatePossibility(0, '4');
		board.EliminatePossibility(0, '5');
		board.EliminatePossibility(0, '6');
		board.EliminatePossibility(0, '7');
		board.EliminatePossibility(0, '8');
		REQUIRE( board.IsSolved(0) == true);
	}
}

TEST_CASE("sudokusolver EliminatePossibilities/GetSolved test") {
	string solution = "";
	SECTION("solved board") {
		SudokuSolver solver = SudokuSolver(puzzle);
		SudokuBoard solved_board= solver.GetSolved();
		REQUIRE((int) solved_board.GetPossibilities(0).at(0) == (int) '7');
		REQUIRE((int) solved_board.GetPossibilities(3).at(0) == (int) '8');
		REQUIRE((int) solved_board.GetPossibilities(78).at(0) == (int) '7');
	}
}
TEST_CASE("sudokusolver EliminateSameBox test") {
	string solution = "";
	SECTION("eliminated possibility of a box") {
		SudokuSolver solver = SudokuSolver(puzzle);
		solver.EliminateSameBox(3);
		SudokuBoard board = solver.GetBoard();
		REQUIRE((int)board.GetPossibilities(3).at(0) == (int) '8');
		REQUIRE((int)board.GetPossibilities(4).size() == 8);
		REQUIRE((int)board.GetPossibilities(14).size() == 8);
		REQUIRE((int)board.GetPossibilities(0).size() == 9);
		REQUIRE((int)board.GetPossibilities(78).size() == 9);
	}
	SECTION("eliminated multiple possibilities of a box") {
		SudokuSolver solver = SudokuSolver(puzzle);
		solver.EliminateSameBox(3);
		solver.EliminateSameBox(5);
		SudokuBoard board = solver.GetBoard();
		REQUIRE((int)board.GetPossibilities(3).at(0) == (int) '8');
		REQUIRE((int)board.GetPossibilities(4).size() == 7);
		REQUIRE((int)board.GetPossibilities(14).size() == 7);
		REQUIRE((int)board.GetPossibilities(0).size() == 9);
		REQUIRE((int)board.GetPossibilities(78).size() == 9);
	}
}
TEST_CASE("sudokusolver EliminateSameLine test") {
	string solution = "";
	SECTION("eliminated possibility of a box") {
		SudokuSolver solver = SudokuSolver(puzzle);
		solver.EliminateSameLine(3);
		SudokuBoard board = solver.GetBoard();
		REQUIRE((int)board.GetPossibilities(3).at(0) == (int) '8');
		REQUIRE((int)board.GetPossibilities(4).size() == 8);
		REQUIRE((int)board.GetPossibilities(14).size() == 9);
		REQUIRE((int)board.GetPossibilities(0).size() == 8);
		REQUIRE((int)board.GetPossibilities(78).size() == 9);
	}
	SECTION("eliminated multiple possibilities of a box") {
		SudokuSolver solver = SudokuSolver(puzzle);
		solver.EliminateSameLine(3);
		solver.EliminateSameLine(5);
		SudokuBoard board = solver.GetBoard();
		REQUIRE((int)board.GetPossibilities(3).at(0) == (int) '8');
		REQUIRE((int)board.GetPossibilities(4).size() == 7);
		REQUIRE((int)board.GetPossibilities(14).size() == 8);
		REQUIRE((int)board.GetPossibilities(12).size() == 8);
		REQUIRE((int)board.GetPossibilities(0).size() == 7);
		REQUIRE((int)board.GetPossibilities(78).size() == 9);
	}
}
TEST_CASE("sudokusolver GetSolved test") {
	SudokuSolver solver = SudokuSolver(puzzle);
	SudokuBoard solved = solver.GetSolved();
	for (int i = 0; i < 81; i++) {
		REQUIRE(solved.IsSolved(i) == true);
	}
}