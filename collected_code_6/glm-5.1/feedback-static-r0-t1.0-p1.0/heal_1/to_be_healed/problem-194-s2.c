#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

long octal_to_decimal(const char *octal_str) {
    if (octal_str == NULL) {
        return -1;
    }

    size_t i = 0;
    long decimal = 0;

    while (isspace((unsigned char)octal_str[i])) {
        i++;
    }

    if (octal_str[i] == '\0') {
        return -1;
    }

    while (octal_str[i] != '\0') {
        if (octal_str[i] < '0' || octal_str[i] > '7') {
            return -1;
        }
        decimal = decimal * 8 + (octal_str[i] - '0');
        i++;
    }

    return decimal;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <octal_number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    long result = octal_to_decimal(argv[1]);
    if (result == -1) {
        fprintf(stderr, "Invalid octal number provided.\n");
        return EXIT_FAILURE;
    }

    printf("%ld\n", result);
    return EXIT_SUCCESS;
}