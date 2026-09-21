#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <errno.h>

int octalToDecimal(long octal) {
    int decimal = 0, i = 0;
    while (octal != 0) {
        decimal += (octal % 10) * (int)pow(8, i);
        ++i;
        octal /= 10;
    }
    return decimal;
}

int main() {
    char input[1024];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Input error\n");
        return EXIT_FAILURE;
    }
    char *end;
    errno = 0;
    long num = strtol(input, &end, 8);
    if (errno == ERANGE || (num == 0 && (end == input || input[0] == '\n')) || *end != '\0' || num < INT_MIN || num > INT_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    printf("%d\n", octalToDecimal((int)num));
    return EXIT_SUCCESS;
}