#include <stdio.h>
#include <stdbool.h>

struct Tuple {
    int a;
    int b;
};

bool containsK(struct Tuple tuples[], int size, int k) {
    for(int i = 0; i < size; i++) {
        if(tuples[i].a == k || tuples[i].b == k) {
            return true;
        }
    }
    return false;
}

int main() {
    struct Tuple tuples[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    int size = sizeof(tuples) / sizeof(tuples[0]);
    int k = 3;

    if(containsK(tuples, size, k)) {
        printf("The tuple contains %d\n", k);
    } else {
        printf("The tuple does not contain %d\n", k);
    }

    return 0;
}