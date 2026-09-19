#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *left_rotate(char *str, int n) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return str;
    }

    size_t shift = ((size_t)n % len);
    if (shift == 0) {
        return str;
    }

    char *temp = (char *)malloc(len + 1);
    if (temp == NULL) {
        return NULL;
    }

    memcpy(temp, str + shift, len - shift);
    memcpy(temp + len - shift, str, shift);
    memcpy(str, temp, len);

    free(temp);

    return str;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <rotate_amount>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *input = (char *)malloc(strlen(argv[1]) + 1);
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    strcpy(input, argv[1]);

    int n = atoi(argv[2]);
    if (n < 0) {
        fprintf(stderr, "Rotate amount must be non-negative\n");
        free(input);
        return EXIT_FAILURE;
    }

    char *result = left_rotate(input, n);
    if (result == NULL) {
        fprintf(stderr, "Rotation failed\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("%s\n", result);

    free(input);

    return EXIT_SUCCESS;
}