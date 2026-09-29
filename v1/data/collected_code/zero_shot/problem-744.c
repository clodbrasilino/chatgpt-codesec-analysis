#include <stdio.h>

typedef struct Tuple {
    int a;
    int b;
    int c;
    int d;
} Tuple;

int checkForNoneValue(Tuple t) {
    if (t.a == 0 || t.b == 0 || t.c == 0 || t.d == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    Tuple tuple = {1, 2, 0, 4};

    if (checkForNoneValue(tuple) == 1) {
        printf("Tuple contains one or more none values\n");
    } else {
        printf("Tuple does not contain any none values\n");
    }

    return 0;
}