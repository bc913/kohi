#ifndef KOHI_1701750954_TEST_MANAGER_H
#define KOHI_1701750954_TEST_MANAGER_H

#include <defines.h>

#define BYPASS 2

typedef u8 (*PFN_test)();

void test_manager_init();

void test_manager_register_test(PFN_test, char* desc);

void test_manager_run_tests();

#endif