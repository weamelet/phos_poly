#include <assert.h>
#include "PhosTests.h"
#include "PhosInterface.c"

void test_polynomial_int() {
    int dat1[3] = {1, 2, 1};
    int dat2[2] = {3, 4};
    int val1 = 2;
    void *res1 = malloc(sizeof(int));
    PhosPoly pol1, pol2, pol3;

    assert(poly_int(2, (void *)dat1, &pol1) == PhosPolyStatusOk);
    assert(poly_int(1, (void *)dat2, &pol2) == PhosPolyStatusOk);
    assert(PhosPolyActions.clc(&pol1, (void *)&val1, &res1) == PhosPolyStatusOk);
    assert(PhosPolyActions.sum(&pol1, &pol2, &pol3) == PhosPolyStatusOk);
    assert(PhosPolyActions.scl(&pol1, (void *)&val1, &pol3) == PhosPolyStatusOk);
    assert(PhosPolyActions.mul(&pol1, &pol2, &pol3) == PhosPolyStatusOk);
    assert(PhosPolyActions.com(&pol1, &pol2, &pol3) == PhosPolyStatusOk);
};

void test_polynomial_float() {
    float dat1[3] = {1.5, 2.5, 1.5};
    float dat2[2] = {-2.5, -3.5};
    float val1 = 2;
    void *res1 = malloc(sizeof(float));
    PhosPoly pol1, pol2, pol3;

    assert(poly_flt(2, (void *)dat1, &pol1) == PhosPolyStatusOk);
    assert(poly_flt(1, (void *)dat2, &pol2) == PhosPolyStatusOk);
    assert(PhosPolyActions.clc(&pol1, (void *)&val1, &res1) == PhosPolyStatusOk);
    assert(PhosPolyActions.sum(&pol1, &pol2, &pol3) == PhosPolyStatusOk);
    assert(PhosPolyActions.scl(&pol1, (void *)&val1, &pol3) == PhosPolyStatusOk);
    assert(PhosPolyActions.mul(&pol1, &pol2, &pol3) == PhosPolyStatusOk);
    assert(PhosPolyActions.com(&pol1, &pol2, &pol3) == PhosPolyStatusOk);
};

void test_operations_int() {
    int a = 2, b = 3;
    void *res = malloc(sizeof(int));
    assert(PhosBaseInt.sum((void *)&a, (void *)&b, &res) == PhosBasicStatusOk);
    assert(PhosBaseInt.mul((void *)&a, (void *)&b, &res) == PhosBasicStatusOk);
    assert(PhosBaseInt.neg((void *)&a, &res) == PhosBasicStatusOk);
    assert(PhosBaseInt.inv((void *)&a, &res) == PhosBasicStatusUndefinedError);
    assert(PhosBaseInt.one(&res) == PhosBasicStatusOk);
    assert(PhosBaseInt.nul(&res) == PhosBasicStatusOk);
};

void test_operations_float() {
    float a = 1.5, b = 2.5;
    void *res = malloc(sizeof(int));
    assert(PhosBaseFlt.sum((void *)&a, (void *)&b, &res) == PhosBasicStatusOk);
    assert(PhosBaseFlt.mul((void *)&a, (void *)&b, &res) == PhosBasicStatusOk);
    assert(PhosBaseFlt.neg((void *)&a, &res) == PhosBasicStatusOk);
    assert(PhosBaseFlt.inv((void *)&a, &res) == PhosBasicStatusOk);
    assert(PhosBaseFlt.one(&res) == PhosBasicStatusOk);
    assert(PhosBaseFlt.nul(&res) == PhosBasicStatusOk);
};

void test_everything() {
    printf("Deploying unit tests...\n");
    printf("Now testing: INT operations...\n");
    test_operations_int();
    printf("Done.\n");
    printf("Now testing: FLOAT operations...\n");
    test_operations_float();
    printf("Done.\n");
    printf("Now testing: INT polynomials...\n");
    test_polynomial_int();
    printf("Done.\n");
    printf("Now testing: FLOAT polynomials...\n");
    test_polynomial_float();
    printf("Done.\n");
    printf("All tests passed.\n");
};