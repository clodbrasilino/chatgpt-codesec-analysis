#include <stdio.h>
#include <stdbool.h>

bool contains_k(int *tuples, int length, int k) {
    for (int i = 0; i < length; i++) {
        if (tuples[i] == k) {
            return true;
        }
    }
    return false;
}

int main() {
    int tuples[] = {1, 2, 3, 4, 5};
    int length = sizeof(tuples) / sizeof(tuples[0]);
    int k = 3;
    
    if (contains_k(tuples, length, k)) {
        printf("The tuple contains %d\n", k);
    } else {
        printf("The tuple does not contain %d\n", k);
    }
    return 0;
}