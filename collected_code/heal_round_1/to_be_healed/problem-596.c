#include <stdio.h>

int tupleSize(char* tuple) {
    int size = 0;
    /* Possible weaknesses found:
     *  Cannot determine that 'tuple[size]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    while (tuple[size] != '\0') {
        size++;
    }
    return size;
}

int main() {
    char tuple[] = "example";
    int size = tupleSize(tuple);
    printf("Size of tuple: %d\n", size);
    return 0;
}