#include <stdio.h>

void tupleAccess(int* tuple, int size) {
    /* Possible weaknesses found:
     *  Cannot determine that 'tuple[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int first = tuple[0];
    /* Possible weaknesses found:
     *  Cannot determine that 'tuple[size-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int last = tuple[size - 1];
    printf("Initial data: %d\n", first);
    printf("Last data: %d\n", last);
}

int main() {
    int tuple[] = {1, 2, 3, 4, 5};
    int size = sizeof(tuple) / sizeof(tuple[0]);
    tupleAccess(tuple, size);
    return 0;
}