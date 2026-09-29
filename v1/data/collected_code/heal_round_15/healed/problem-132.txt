#include <stdio.h>
#include <string.h>

#define MAX_SIZE 128

void tupleToStringSafe(char* str, const size_t size, const int tuple) {
    size_t required_size = snprintf(NULL, 0, "(%d, %d, %d)", tuple >> 16, (tuple >> 8) & 0xFF, tuple & 0xFF) + 1;

    if (required_size >= size) {
        snprintf(str, size, "Buffer size too small\n");
    } else {
        snprintf(str, required_size, "(%d, %d, %d)", tuple >> 16, (tuple >> 8) & 0xFF, tuple & 0xFF);
    }
}

int main() {
    int tuple = 0x123456;
    char str[MAX_SIZE];

    tupleToStringSafe(str, sizeof(str), tuple);

    if (strcmp(str, "Buffer size too small\n") != 0) {
        printf("%s\n", str);
    }

    return 0;
}