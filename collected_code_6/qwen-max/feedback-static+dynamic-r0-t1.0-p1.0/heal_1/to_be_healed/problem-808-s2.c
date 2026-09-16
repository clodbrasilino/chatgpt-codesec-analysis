#include <stdio.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'tuples' can be declared as pointer to const [constParameterPointer]
 */
bool contains_k(int *tuples, int n, int k) {
    for (int i = 0; i < n; i++) {
        if (tuples[i] == k) {
            return true;
        }
    }
    return false;
}

int main() {
    int tuples[] = {1, 2, 3, 4, 5, 6};
    int n = sizeof(tuples) / sizeof(tuples[0]);
    int k = 3;

    bool result = contains_k(tuples, n, k);

    if (result) {
        printf("The tuple contains %d\n", k);
    } else {
        printf("The tuple does not contain %d\n", k);
    }

    return 0;
}