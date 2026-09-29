#include <stdio.h>
#include <stdlib.h>

#define MAX_TUPLE_SIZE 100

void tupleToDictionary(int tuple[], int tuple_size, int dictionary[]) {
    int i;
    for (i = 0; i < tuple_size - 1; i += 2) {
        /* Possible weaknesses found:
         *  Cannot determine that 'tuple[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'tuple[i+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        dictionary[tuple[i]] = tuple[i + 1];
    }
}

int main() {
    int tuple[] = {1, 10, 2, 20, 3, 30, 4, 40};
    int tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    int dictionary[MAX_TUPLE_SIZE] = {0};

    tupleToDictionary(tuple, tuple_size, dictionary);

    int i;
    for (i = 0; i < tuple_size - 1; i += 2) {
        printf("%d: %d\n", dictionary[tuple[i]], dictionary[tuple[i + 1]]);
    }

    return 0;
}