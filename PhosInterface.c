#include "PhosInterface.h"

void interface_start() {
    printf("---\n");
    printf("Welcome to the Phos Polymorphic Polynome interactive demonstration.\n");
    printf("Created by Dmitry Chernov, B23-504 circa April 2024.\n");
    int choice = 0, len = 0;
    PhosPoly **pol = NULL;
    while (1) {
        printf("---\n");
        printf("Please choose one of the following options to proceed:\n");
        printf("(1) Save new polynomial to memory.\n");
        printf("(2) Add two already stored polynomials and save the result.\n");
        printf("(3) Multiply two already stored polynomials and save the result.\n");
        printf("(4) Compose two already stored polynomials and save the result.\n");
        printf("(5) Display all currently stored polynomials.\n");
        printf("<Your choice> ");
        scanf("%d", &choice);
        if (choice == 1) {
            new_poly(&pol, &len);
        } else if (choice == 2) {
            add_poly(&pol, &len);
        } else if (choice == 3) {
            mul_poly(&pol, &len);
        } else if (choice == 4) {
            comp_poly(&pol, &len);
        } else if (choice == 5) {
            print_poly(pol, &len);
        } else {
            printf("---\n");
            printf("Invalid input, please try again.\n");
        }
    }
};

void new_poly(PhosPoly ***pol, int *len) {
    int polt = 0, pow = 0;
    void *dat;
    printf("---\n");
    printf("Enter the type of polynomial to add:\n");
    printf("(1) Integer polynomial.\n");
    printf("(2) Floating-point polynomial.\n");
    printf("<Your choice> ");
    scanf("%d", &polt);
    if (polt != 1 && polt != 2) {
        printf("---\n");
        printf("Invalid input, operation interrupted.\n");
        return;
    }
    printf("---\n");
    printf("Enter the degree of polynomial (0 - 100 inclusive):\n");
    printf("<Your input> ");
    scanf("%d", &pow);
    if (pow < 0 || pow > 100) {
        printf("---\n");
        printf("Invalid input, operation interrupted.\n");
        return;
    }
    if (polt == 1) {
        dat = malloc (sizeof(int) * (pow + 1));
    } else if (polt == 2) {
        dat = malloc (sizeof(float) * (pow + 1));
    }
    printf("---\n");
    printf("Enter the coefficients:\n");
    printf("<Your input> ");
    for (int pos = 0; pos <= pow; pos++) {
        if (polt == 1) {
            int pot = 0;
            scanf("%d", &pot);
            ((int *)dat)[pos] = pot;
        } else if (polt == 2) {
            float pot = 0;
            scanf("%f", &pot);
            ((float *)dat)[pos] = pot;
        }
    }
    *len = *len + 1;
    *pol = realloc(*pol, sizeof(PhosPoly*) * (*len));
    PhosPoly *pon = malloc(sizeof(PhosPoly));
    if (polt == 1) {
        poly_int(pow, dat, pon);
    } else if (polt == 2) {
        poly_flt(pow, dat, pon);
    }
    (*pol)[*len - 1] = pon;
    dat = (*pol)[*len - 1]->dat;
    return;
};

void add_poly(PhosPoly ***pol, int *len) {
    int a = 0, b = 0;
    printf("---\n");
    printf("Enter the indices of polynomials to add:\n");
    printf("<Your input> ");
    scanf("%d %d", &a, &b);
    if (!(a >= 0 && a < *len && b >= 0 && b < *len)) {
        printf("---\n");
        printf("Invalid input, operation interrupted.\n");
        return;
    }
    *len = *len + 1;
    *pol = realloc(*pol, sizeof(PhosPoly*) * (*len));
    PhosPoly *pon = malloc(sizeof(PhosPoly));
    PhosPolyActions.sum((*pol)[a], (*pol)[b], pon);
    (*pol)[*len - 1] = pon;
    return;
};

void mul_poly(PhosPoly ***pol, int *len) {
    int a = 0, b = 0;
    printf("---\n");
    printf("Enter the indices of polynomials to multiply:\n");
    scanf("%d %d", &a, &b);
    if (!(a >= 0 && a < *len && b >= 0 && b < *len)) {
        printf("---\n");
        printf("Invalid input, operation interrupted.\n");
        return;
    }
    *len = *len + 1;
    *pol = realloc(*pol, sizeof(PhosPoly*) * (*len));
    PhosPoly *pon = malloc(sizeof(PhosPoly));
    PhosPolyActions.mul((*pol)[a], (*pol)[b], pon);
    (*pol)[*len - 1] = pon;
    return;
}
void comp_poly(PhosPoly ***pol, int *len) {
    int a = 0, b = 0;
    printf("---\n");
    printf("Enter the indices of polynomials to perform convolution on:\n");
    scanf("%d %d", &a, &b);
    if (!(a >= 0 && a < *len && b >= 0 && b < *len)) {
        printf("---\n");
        printf("Invalid input, operation interrupted.\n");
        return;
    }
    *len = *len + 1;
    *pol = realloc(*pol, sizeof(PhosPoly*) * (*len));
    PhosPoly *pon = malloc(sizeof(PhosPoly));
    PhosPolyActions.com((*pol)[a], (*pol)[b], pon);
    
    (*pol)[*len - 1] = pon;
    return;
};

void print_poly(PhosPoly **pol, int *len) {
    printf("---\n");
    printf("The polynomials currently stored are listed below.\n");
    for (int pos = 0; pos < *len; pos++) {
        printf("(%d) Polynomial of degree %d.\n", pos, pol[pos]->pow);
        printf("    Coefficients: ");
        for (int pow = 0; pow <= pol[pos]->pow; pow++) {
            void *coef = malloc(pol[pos]->bas->len);
            pol[pos]->bas->get(pol[pos]->dat, pow, &coef);
            pol[pos]->bas->log(coef);
            printf(" ");
        }
        printf("\n");
    };
};
