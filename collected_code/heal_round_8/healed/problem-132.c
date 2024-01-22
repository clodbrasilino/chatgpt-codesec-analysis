#include <stdio.h>
#include <string.h>

#define MAX_SIZE 128

void tupleToStringSafe(char* str, const int size, const int tuple) {
    if (size >= MAX_SIZE) {
        snprintf(str, size - 1, "(%d, %d, %d)", tuple >> 16, (tuple >> 8) & 0xFF, tuple & 0xFF);
        str[size - 1] = '\0';
    } else {
        printf("Buffer size too small\n");
    }
}

int main() {
    int tuple = 0x123456;
    char str[MAX_SIZE];

    tupleToStringSafe(str, sizeof(str), tuple);

    printf("%s\n", str);

    return 0;
}