#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

void remove_chars(char *str, const char *mask);

void remove_chars(char *str, const char *mask)
{
    bool present[256] = { false };
    size_t i;
    size_t j;

    if (str == NULL || mask == NULL) {
        return;
    }

    for (i = 0; mask[i] != '\0'; i++) {
        present[(unsigned char)mask[i]] = true;
    }

    j = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (!present[(unsigned char)str[i]]) {
            str[j] = str[i];
            j++;
        }
    }
    str[j] = '\0';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char first[256];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char second[256];
    size_t len;

    printf("Enter the first string: ");
    if (fgets(first, sizeof(first), stdin) == NULL) {
        fprintf(stderr, "Error reading first string\n");
        return EXIT_FAILURE;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(first);
    if (len > 0 && first[len - 1] == '\n') {
        first[len - 1] = '\0';
    }

    printf("Enter the second string: ");
    if (fgets(second, sizeof(second), stdin) == NULL) {
        fprintf(stderr, "Error reading second string\n");
        return EXIT_FAILURE;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(second);
    if (len > 0 && second[len - 1] == '\n') {
        second[len - 1] = '\0';
    }

    remove_chars(first, second);

    printf("Result: %s\n", first);

    return EXIT_SUCCESS;
}