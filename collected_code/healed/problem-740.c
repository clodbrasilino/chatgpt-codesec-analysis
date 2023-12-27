#include <stdio.h>
#include <stdlib.h>

#define MAX_TUPLE_SIZE 100

void tupleToDictionary(const int tuple[], int tuple_size, int dictionary[]) {
    int i;
    for (i = 0; i < tuple_size - 1; i += 2) {
        dictionary[tuple[i]] = tuple[i + 1];
    }
}

int main() {
    const int tuple[] = {1, 10, 2, 20, 3, 30, 4, 40};
    int tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    int dictionary[MAX_TUPLE_SIZE] = {0};

    tupleToDictionary(tuple, tuple_size, dictionary);

    int i;
    for (i = 0; i < tuple_size; i += 2) {
        printf("%d: %d\n", tuple[i], dictionary[tuple[i]]);
    }

    return 0;
}