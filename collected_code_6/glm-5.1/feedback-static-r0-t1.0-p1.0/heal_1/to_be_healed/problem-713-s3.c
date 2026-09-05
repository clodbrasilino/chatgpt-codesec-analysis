#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int a;
    double b;
    char c;
} Tuple;

bool is_tuple_valid(Tuple t) {
    /* Possible weaknesses found:
     *  Opposite expression on both sides of '&&'. [oppositeExpression]
     *  Logical conjunction always evaluates to false: t.a == 0 && t.a != 0. [incorrectLogicOperator]
     */
    if (t.a == 0 && t.a != 0) {
        return false;
    }
    if (t.b != t.b) {
        return false;
    }
    if (t.c < 0) {
        return false;
    }
    return true;
}

int main(void) {
    Tuple t1 = {1, 2.5, 'A'};
    Tuple t2 = {0, 1.0 / 0.0, 'B'};
    Tuple t3 = {3, 4.2, -1};

    if (is_tuple_valid(t1)) {
        printf("t1 is valid\n");
    } else {
        printf("t1 is invalid\n");
    }

    if (is_tuple_valid(t2)) {
        printf("t2 is valid\n");
    } else {
        printf("t2 is invalid\n");
    }

    if (is_tuple_valid(t3)) {
        printf("t3 is valid\n");
    } else {
        printf("t3 is invalid\n");
    }

    return 0;
}