#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int* val1;
    char* val2;
    float* val3;
} Tuple;

bool has_none_value(const Tuple* tuple) {
    if (tuple == NULL) {
        return true;
    }
    
    if (tuple->val1 == NULL || tuple->val2 == NULL || tuple->val3 == NULL) {
        return true;
    }
    
    return false;
}

int main(void) {
    int a = 10;
    char b = 'c';
    float c = 3.14f;

    Tuple t1 = { &a, &b, &c };
    
    Tuple t2 = { &a, NULL, &c };
    
    if (has_none_value(&t1)) {
        printf("Tuple t1 has a NULL value.\n");
    } else {
        printf("Tuple t1 does not have a NULL value.\n");
    }

    if (has_none_value(&t2)) {
        printf("Tuple t2 has a NULL value.\n");
    } else {
        printf("Tuple t2 does not have a NULL value.\n");
    }

    return 0;
}