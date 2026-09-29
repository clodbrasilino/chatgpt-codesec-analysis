#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void reverse_range(char *start, char *end)
{
    while (start < end) {
        char temp = *start;
        *start++ = *end;
        *end-- = temp;
    }
}

static int left_rotate(char *string, size_t positions)
{
    if (string == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(string);

    if (length == 0) {
        return 0;
    }

    positions %= length;

    if (positions == 0) {
        return 0;
    }

    reverse_range(string, string + positions - 1);
    reverse_range(string + positions, string + length - 1);
    reverse_range(string, string + length - 1);

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char string[1024];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end = NULL;

    if (fgets(string, sizeof(string), stdin) == NULL) {
        fputs("Failed to read the string.\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(string);

    if (length > 0 && string[length - 1] == '\n') {
        string[length - 1] = '\0';
    } else if (!feof(stdin)) {
        fputs("Input string is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fputs("Failed to read the rotation count.\n", stderr);
        return EXIT_FAILURE;
    }

    if (input[0] == '-') {
        fputs("Rotation count must be nonnegative.\n", stderr);
        return EXIT_FAILURE;
    }

    unsigned long long value = strtoull(input, &end, 10);

    if (end == input || (*end != '\n' && *end != '\0')) {
        fputs("Invalid rotation count.\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t string_length = strlen(string);
    size_t positions = string_length == 0
        ? 0
        : (size_t)(value % (unsigned long long)string_length);

    if (left_rotate(string, positions) != 0) {
        fputs("Failed to rotate the string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(string) == EOF) {
        fputs("Failed to write the result.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}