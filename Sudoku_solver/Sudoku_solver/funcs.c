#include "funcs.h"

unsigned int char_to_digit(char ch) {
	return ch - '0';
}

sudoku_board* create_sudoku_board(char** lines, int count) {
	sudoku_board* sudoku_board = (struct sudoku_board*)malloc(sizeof(sudoku_board));
	unsigned int** matr_sudoku_board = (unsigned int**)malloc(sizeof(unsigned int*) * count);

	for (int i = 0; i < count; ++i) {
		matr_sudoku_board[i] = (unsigned int*)malloc(sizeof(unsigned int*) * count);

		for (int j = 0; lines[i][j] != '\0'; ++j) {
			if (lines[i][j] == '.') {
				matr_sudoku_board[i][j] = 0;
			}
			else {
				matr_sudoku_board[i][j] = char_to_digit(lines[i][j]);
			}
		}
	}

	sudoku_board->matr_sudoku_board = matr_sudoku_board;
	sudoku_board->size = count;
	return sudoku_board;
}

void remove_sudoku_board(sudoku_board* sudoku_board) {
	for (unsigned int i = 0; i < sudoku_board->size; ++i) {
		free(sudoku_board->matr_sudoku_board[i]);
	}
	free(sudoku_board->matr_sudoku_board);
	//free(sudoku_board);
}

matr_of_possible_values* create_matr_of_possible_values(const sudoku_board* sudoku_board) {
	matr_of_possible_values* matr_of_possible_values = (struct matr_of_possible_values*)malloc(sizeof(matr_of_possible_values));
	int** matr = (int**)malloc(sizeof(int*) * (sudoku_board->size * sudoku_board->size));

	for (unsigned int i = 0; i < sudoku_board->size * sudoku_board->size; ++i) {
		matr[i] = (int*)malloc(sizeof(int) * (sudoku_board->size));
		for (unsigned int j = 0; j < sudoku_board->size; ++j) {
			matr[i][j] = 1;
		}
	}

	matr_of_possible_values->matr_of_possible_values = matr;
	matr_of_possible_values->size = sudoku_board->size;

	return matr_of_possible_values;
}

void fill_matr_of_possible_values(matr_of_possible_values* matr, const sudoku_board* sudoku_board) {
	for (unsigned int board_row = 0; board_row < sudoku_board->size; ++board_row) {
		for (unsigned int board_col = 0; board_col < sudoku_board->size; ++board_col) {
			if (sudoku_board->matr_sudoku_board[board_row][board_col] != 0) {
				matr->matr_of_possible_values[matr->size * board_row + board_col][0] = -1;
			}
			else {
				for (unsigned int dot_col = 0; dot_col < sudoku_board->size; ++dot_col) {
					unsigned int digit_on_board = sudoku_board->matr_sudoku_board[board_row][dot_col];
					if (digit_on_board != 0) {
						matr->matr_of_possible_values[matr->size * board_row + board_col][digit_on_board - 1] = 0;
					}
				}
				for (unsigned int dot_row = 0; dot_row < sudoku_board->size; ++dot_row) {
					unsigned int digit_on_board = sudoku_board->matr_sudoku_board[dot_row][board_col];
					if (digit_on_board != 0) {
						matr->matr_of_possible_values[matr->size * board_row + board_col][digit_on_board - 1] = 0;
					}
				}
				unsigned int min_col_square = (board_col / 3) * 3;
				unsigned int min_row_square = (board_row / 3) * 3;
				for (unsigned int row_square = min_row_square; row_square < min_row_square + 3; ++row_square) {
					for (unsigned int col_square = min_col_square; col_square < min_col_square + 3; ++col_square) {
						unsigned int digit_on_board = sudoku_board->matr_sudoku_board[row_square][col_square];
						if (digit_on_board != 0) {
							matr->matr_of_possible_values[matr->size * board_row + board_col][digit_on_board - 1] = 0;
						}
					}
				}
			}
		}
	}
}

matr_of_possible_values* create_copy_of_possible_values(const matr_of_possible_values* matr, const sudoku_board* sudoku_board) {
	matr_of_possible_values* copy = create_matr_of_possible_values(sudoku_board);
	for (unsigned int i = 0; i < matr->size * matr->size; ++i) {
		for (unsigned int j = 0; j < matr->size; ++j) {
			copy->matr_of_possible_values[i][j] = matr->matr_of_possible_values[i][j];
		}
	}
	return copy;
}

void remove_matr_of_possible_values(matr_of_possible_values* matr) {
	for (unsigned int i = 0; i < matr->size; ++i) {
		free(matr->matr_of_possible_values[i]);
	}
	free(matr->matr_of_possible_values);
	//free(matr);
}

int can_be_solved(matr_of_possible_values* matr, int number) {
	int possible_values = 0;
	if (matr->matr_of_possible_values[number][0] == -1) {
		return 0;
	}
	for (int i = 0; i < matr->size; ++i) {
		if (matr->matr_of_possible_values[number][i] == 1) {
			possible_values++;
		}
	}
	if (possible_values == 1) {
		return 1;
	}
	else {
		return 0;
	}
}

int real_value_of_number(matr_of_possible_values* matr, int number) {
	for (int i = 0; i < matr->size; ++i) {
		if (matr->matr_of_possible_values[number][i] == 1) {
			return i + 1;
		}
	}
	return -1;
}

int number_of_dots(const matr_of_possible_values* matr_of_possible_values)
{
	int counter = 0;
	for (int i = 0; i < matr_of_possible_values->size * matr_of_possible_values->size; ++i) {
		if (matr_of_possible_values->matr_of_possible_values[i][0] != -1) {
			counter++;
		}
	}
	return counter;
}
