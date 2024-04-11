#include "PhosBasic.c"

typedef enum PhosPolyStatus {
    PhosPolyStatusOk,
    PhosPolyStatusError
} PhosPolyStatus;

typedef struct PhosPoly {
    int pow;
    void *dat;
    const PhosBase *bas;
} PhosPoly;

PhosPolyStatus poly_int(int pow, void *dat, PhosPoly *pol);
PhosPolyStatus poly_flt(int pow, void *dat, PhosPoly *pol);

typedef struct PhosPolyActionsLibrary {
    PhosPolyStatus (*clc) (PhosPoly *pol, void *opa, void **res);
    PhosPolyStatus (*sum) (PhosPoly *pol, PhosPoly *pom, PhosPoly *res);
    PhosPolyStatus (*scl) (PhosPoly *pol, void *opa, PhosPoly *res);
    PhosPolyStatus (*mul) (PhosPoly *pol, PhosPoly *pom, PhosPoly *res);
    PhosPolyStatus (*com) (PhosPoly *pol, PhosPoly *pom, PhosPoly *res);
} PhosPolyActionsLibrary;

extern const PhosPolyActionsLibrary PhosPolyActions;
