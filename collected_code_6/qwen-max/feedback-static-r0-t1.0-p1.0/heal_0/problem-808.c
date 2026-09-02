#include <stdio.h>
#include <stdbool.h>

bool contains_k(int *tuple, int length, int k) {
    for (int i = 0; i < length; ++i) {
        if (tuple[i] == k) {
            return true;
        }
    }
    return false;
}

int main(void) {
    int tuple[] = {1, 2, 3, 4, 5};
    int length = sizeof(tuple) / sizeof(tuple[0]);
    int k = 3;

    bool result = contains_k(tuple, length, k);
    if (result) {
        printf("The tuple contains %d\n", k);
    } else {
        printf("The tuple does not contain %d\n", k);
    }

    return 0;
}