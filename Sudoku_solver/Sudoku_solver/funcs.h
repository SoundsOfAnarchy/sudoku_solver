#ifndef FUNCS_H
#define FUNCS_H

struct sudoku_board {
	unsigned int** matr_sudoku_board;
	unsigned int size;
} typedef sudoku_board;

struct matr_of_possible_values {
	int** matr_of_possible_values;
	unsigned int size;
} typedef matr_of_possible_values;

unsigned int char_to_digit(char ch);

sudoku_board* create_sudoku_board(char** lines, int count);

void remove_sudoku_board(sudoku_board* sudoku_board);

matr_of_possible_values* create_matr_of_possible_values(const sudoku_board* sudoku_board);

void fill_matr_of_possible_values(matr_of_possible_values* matr, const sudoku_board* sudoku_board);

matr_of_possible_values* create_copy_of_possible_values(const matr_of_possible_values* matr, const sudoku_board* sudoku_board);

void remove_matr_of_possible_values(matr_of_possible_values* matr_of_possible_values);

int number_of_dots(const matr_of_possible_values* matr_of_possible_values);

int can_be_solved(matr_of_possible_values* matr, int number);

int real_value_of_number(matr_of_possible_values* matr, int number);

#endif // !FUNCS_H

