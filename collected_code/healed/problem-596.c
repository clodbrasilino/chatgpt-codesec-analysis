#include <stdio.h>

int tupleSize(const char* tuple) {
    int size = 0;
    while (tuple[size] != '\0') {
        size++;
    }
    return size;
}

int main() {
    const char tuple[] = "example";
    int size = tupleSize(tuple);
    printf("Size of tuple: %d\n", size);
    return 0;
}