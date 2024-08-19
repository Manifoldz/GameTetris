#include "../../inc/backend.h"

void loadSaveRecord(bool is_save, int *record, const char *filename) {
  FILE *file;
  if (is_save) {
    file = fopen(filename, "w");
    if (file != NULL) {
      fprintf(file, "%d", *record);
    }
  } else {
    file = fopen(filename, "r");
    int temp = 0;
    if (file != NULL) {
      fscanf(file, "%d", &temp);
    }
    *record = temp < 0 ? 0 : temp;
  }
  if (file != NULL) {
    fclose(file);
  }
}

void *safeMalloc(size_t size, Error_t *err) {
  void *ptr = NULL;
  if (err && *err == kOk) {
    if (size > 0) {
      ptr = malloc(size);
      if (!ptr) {
        *err = kErrMem;
      }
    } else {
      *err = kErrIncorrect;
    }
  }
  return ptr;
}

int upDivide(int dividend, int divisor) {
  return (dividend + divisor - 1) / divisor;
}

void swap(int *a, int *b) {
  if (a && b) {
    int temp = *a;
    *a = *b;
    *b = temp;
  }
}