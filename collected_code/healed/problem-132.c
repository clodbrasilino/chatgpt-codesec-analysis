#include <stdio.h>
#include <string.h>

void tupleToString(char *str, int size, int tuple) {
    snprintf(str, size, "(%d, %d, %d)", tuple >> 16, (tuple >> 8) & 0xFF, tuple & 0xFF);
}

int main() {
    int tuple = 0x123456;
    char str[32];

    tupleToString(str, sizeof(str), tuple);

    printf("%s\n", str);

    return 0;
}