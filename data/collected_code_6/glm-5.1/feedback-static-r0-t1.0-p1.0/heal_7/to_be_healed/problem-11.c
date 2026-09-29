#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_first_last(char *str, char c) {
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        return;
    }

    char *first = strchr(str, c);
    if (first == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    memmove(first, first + 1, strlen(first));

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    if (len == 0) {
        return;
    }

    char *last = strrchr(str, c);
    if (last == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    memmove(last, last + 1, strlen(last));
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <char>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t arg_len = strnlen(argv[2], 2);
    if (arg_len != 1) {
        fprintf(stderr, "Error: Second argument must be a single character.\n");
        return EXIT_FAILURE;
    }

    char c = argv[2][0];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_size = strlen(argv[1]) + 1;

    char *str = malloc(str_size);
    if (str == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(str, argv[1], str_size - 1);
    str[str_size - 1] = '\0';

    remove_first_last(str, c);

    printf("%s\n", str);

    free(str);

    return EXIT_SUCCESS;
}