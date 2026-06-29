/**
 * @file test_framework.h
 * @brief Minimal single-header C unit-test framework (no external dependencies)
 */
#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>
#include <math.h>

static int _tf_count = 0;
static int _tf_pass  = 0;
static int _tf_fail  = 0;

#define ASSERT_TRUE(cond) do {                                          \
    _tf_count++;                                                        \
    if (cond) { _tf_pass++; }                                          \
    else {                                                              \
        _tf_fail++;                                                     \
        printf("  FAIL  %-60s  line %d\n", #cond, __LINE__);           \
    }                                                                   \
} while (0)

#define ASSERT_INT_EQ(expected, actual) do {                            \
    _tf_count++;                                                        \
    int _e = (int)(expected), _a = (int)(actual);                      \
    if (_e == _a) { _tf_pass++; }                                      \
    else {                                                              \
        _tf_fail++;                                                     \
        printf("  FAIL  expected %d, got %d  (%s vs %s)  line %d\n",  \
               _e, _a, #expected, #actual, __LINE__);                  \
    }                                                                   \
} while (0)

#define ASSERT_DBL_NEAR(expected, actual, tol) do {                     \
    _tf_count++;                                                        \
    double _e = (double)(expected);                                     \
    double _a = (double)(actual);                                       \
    double _t = (double)(tol);                                          \
    if (fabs(_e - _a) <= _t) { _tf_pass++; }                           \
    else {                                                              \
        _tf_fail++;                                                     \
        printf("  FAIL  expected %.4f, got %.4f (tol %.4f)  line %d\n",\
               _e, _a, _t, __LINE__);                                  \
    }                                                                   \
} while (0)

#define RUN_SUITE(fn) do { printf("\n[Suite] %s\n", #fn); fn(); } while (0)

#define TEST_REPORT() do {                                              \
    printf("\n=========================================\n");            \
    printf("Results: %d passed / %d failed / %d total\n",              \
           _tf_pass, _tf_fail, _tf_count);                             \
    printf("=========================================\n");             \
} while (0)

#define TEST_MAIN_RETURN() return (_tf_fail > 0 ? 1 : 0)

#endif /* TEST_FRAMEWORK_H */
