#include <stdio.h>
#include <string.h>

#define MAX_SIZE 128

void tupleToStringSafe(char* str, int size, int tuple) {
    if (size < MAX_SIZE) {
        printf("Buffer size too small\n");
        return;
    }
    snprintf(str, size, "(%d, %d, %d)", tuple >> 16, (tuple >> 8) & 0xFF, tuple & 0xFF);
}

int main() {
    int tuple = 0x123456;
    char str[MAX_SIZE];

    tupleToStringSafe(str, sizeof(str), tuple);

    printf("%s\n", str);

    return 0;
}