#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

bool tuple_contains(const Tuple *t, int k) {
    if (t == NULL || t->data == NULL) {
        return false;
    }
    
    for (size_t i = 0; i < t->size; i++) {
        if (t->data[i] == k) {
            return true;
        }
    }
    return false;
}

int main(void) {
    int values1[] = {1, 2, 3, 4, 5};
    int values2[] = {10, 20, 30};
    
    Tuple t1 = {values1, sizeof(values1) / sizeof(values1[0])};
    Tuple t2 = {values2, sizeof(values2) / sizeof(values2[0])};
    Tuple t3 = {NULL, 0};
    
    printf("Tuple 1 contains 3: %s\n", tuple_contains(&t1, 3) ? "true" : "false");
    printf("Tuple 1 contains 10: %s\n", tuple_contains(&t1, 10) ? "true" : "false");
    printf("Tuple 2 contains 20: %s\n", tuple_contains(&t2, 20) ? "true" : "false");
    printf("Tuple 3 contains 5: %s\n", tuple_contains(&t3, 5) ? "true" : "false");
    
    return 0;
}