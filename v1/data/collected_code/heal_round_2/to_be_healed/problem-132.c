#include <stdio.h>
#include <string.h>

void tupleToString(char *str, int size, int tuple) {
    snprintf(str, size, "(%d, %d, %d)", tuple >> 16, (tuple >> 8) & 0xFF, tuple & 0xFF);
}

int main() {
    int tuple = 0x123456;
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[32];

    tupleToString(str, sizeof(str), tuple);

    printf("%s\n", str);

    return 0;
}