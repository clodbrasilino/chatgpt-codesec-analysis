#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Possible weaknesses found:
 *  Parameter 'tuple' can be declared as const array [constParameter]
 */
int multiplyAdjacent(int tuple[], int size) {
    assert(size >= 2);
    int result = 1;
    for (int i = 0; i < size - 1; i++) {
        result *= tuple[i] * tuple[i + 1];
    }
    return result;
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5};
    int size = sizeof(tuple) / sizeof(tuple[0]);
    int result = multiplyAdjacent(tuple, size);
    printf("Result: %d\n", result);
    return 0;
}