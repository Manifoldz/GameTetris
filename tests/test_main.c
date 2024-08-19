#include "../inc/test.h"
#define NUMBER_SUITES 6

int main(void) {
  int nf = 0;

  Suite *arrSuites[NUMBER_SUITES] = {test_array2d_matrix(), test_tetromino(),
                                     test_game_field(),     test_common(),
                                     test_param_gameinfo(), test_fsm()};
  for (int i = 0; i < NUMBER_SUITES; i++) {
    SRunner *sr = srunner_create(arrSuites[i]);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    nf += srunner_ntests_failed(sr);
    srunner_free(sr);
  }

  return nf == 0 ? 0 : 1;
}

void fillMatrix1toN(Matrix_t *matrix) {
  if (matrix) {
    int counter = 1;
    for (int i = 0; i < matrix->rows; i++) {
      for (int j = 0; j < matrix->cols; j++) {
        matrix->arr[i][j] = counter++;
      }
    }
  }
}

void printMatrix(Matrix_t *matrix) {
  putchar('\n');
  if (!matrix) {
    puts("NULL!");
    return;
  }
  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->cols; j++) {
      printf("%2d ", matrix->arr[i][j]);
    }
    putchar('\n');
  }
}

void *mock_malloc(size_t size) {
  size = size;
  return NULL;
}