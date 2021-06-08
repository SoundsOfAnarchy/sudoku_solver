#include "funcs.h"

#include <stdio.h>

int main(char* argv[], int argc) {
	char* lines[] = { "1..489..6\0",
						"73..5..4.\0",
						"46...1295\0",
						"38712.6..\0",
						"5.17.3..8\0",
						".46.9571.\0",
						"9146...8.\0",
						".2..4..37\0",
						"8.3512..4\0" };

	struct sudoku_board* sb = create_sudoku_board(lines, 9);
	struct matr_of_possible_values* possible_values = create_matr_of_possible_values(sb);
	fill_matr_of_possible_values(possible_values, sb);

	int dots = number_of_dots(possible_values);

	while (dots != 0) {
		int sudoku_correct = 0;
		for (int i = 0; i < possible_values->size * possible_values->size; ++i) {
			if (can_be_solved(possible_values, i)) {
				sb->matr_sudoku_board[i / 9][i % 9] = real_value_of_number(possible_values, i);
				sudoku_correct = 1;
			}
		}
		if (!sudoku_correct) {
			printf("Error\n");
			return -1;
		}
		fill_matr_of_possible_values(possible_values, sb);
		dots = number_of_dots(possible_values);
	}

	remove_sudoku_board(sb);
	remove_matr_of_possible_values(possible_values);

	for (int i = 0; i < sb->size; ++i) {
		for (int j = 0; j < sb->size; ++j) {
			printf("%d ", sb->matr_sudoku_board[i][j]);
		}
		printf("\n");
	}
	return 0;
}