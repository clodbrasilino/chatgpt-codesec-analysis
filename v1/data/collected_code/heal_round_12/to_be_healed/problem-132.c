#include <stdio.h>
#include <string.h>

#define MAX_SIZE 128

void tupleToStringSafe(char* str, const size_t size, const int tuple) {
    if (size < MAX_SIZE) {
        snprintf(str, size - 1, "Buffer size too small\n");
        return;
    }
    snprintf(str, size - 1, "(%d, %d, %d)", tuple >> 16, (tuple >> 8) & 0xFF, tuple & 0xFF);
    str[size - 1] = '\0';
}

int main() {
    int tuple = 0x123456;
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_SIZE];

    tupleToStringSafe(str, sizeof(str), tuple);

    if (strcmp(str, "Buffer size too small\n") != 0) {
        printf("%s\n", str);
    }

    return 0;
}