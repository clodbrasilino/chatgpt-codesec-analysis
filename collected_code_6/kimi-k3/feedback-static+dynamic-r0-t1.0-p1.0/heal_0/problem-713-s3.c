#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int id;
    int value;
    double weight;
    char status;
} Tuple;

bool is_valid_tuple(const Tuple *t) {
    if (t == NULL) {
        return false;
    }
    if (t->id < 0) {
        return false;
    }
    if (t->value < 0 || t->value > 1000) {
        return false;
    }
    if (t->weight < 0.0 || t->weight > 500.0) {
        return false;
    }
    if (t->status != 'A' && t->status != 'I' && t->status != 'P') {
        return false;
    }
    return true;
}

int main(void) {
    Tuple t1 = {1, 100, 50.5, 'A'};
    Tuple t2 = {-1, 200, 60.0, 'I'};
    Tuple t3 = {3, 1500, 70.0, 'P'};
    Tuple t4 = {4, 500, -10.0, 'A'};
    Tuple t5 = {5, 600, 100.0, 'X'};

    printf("t1 valid: %s\n", is_valid_tuple(&t1) ? "true" : "false");
    printf("t2 valid: %s\n", is_valid_tuple(&t2) ? "true" : "false");
    printf("t3 valid: %s\n", is_valid_tuple(&t3) ? "true" : "false");
    printf("t4 valid: %s\n", is_valid_tuple(&t4) ? "true" : "false");
    printf("t5 valid: %s\n", is_valid_tuple(&t5) ? "true" : "false");

    return 0;
}