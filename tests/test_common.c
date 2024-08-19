#include "../inc/test.h"

START_TEST(test_safeMalloc1) {
  Error_t err = kOk;
  ck_assert_ptr_null(safeMalloc(0, &err));
  ck_assert_ptr_null(safeMalloc(8, NULL));
  err = kErrMem;
  ck_assert_ptr_null(safeMalloc(8, &err));
}
END_TEST

START_TEST(test_loadSaveRecord1) {
  int record = 12345;
  loadSaveRecord(true, &record, "test_loadSaveRecord.gc");
  FILE *file = fopen("test_loadSaveRecord.gc", "r");
  ck_assert_ptr_nonnull(file);
  int from_file = 0;
  fscanf(file, "%d", &from_file);
  ck_assert_int_eq(record, from_file);
  fclose(file);
  record = 0;
  loadSaveRecord(false, &record, "test_loadSaveRecord.gc");
  ck_assert_int_eq(record, from_file);
}
END_TEST

Suite *test_common(void) {
  Suite *s = suite_create("common");
  TCase *tc_core = tcase_create("common");

  tcase_add_test(tc_core, test_safeMalloc1);
  tcase_add_test(tc_core, test_loadSaveRecord1);

  suite_add_tcase(s, tc_core);

  return s;
}