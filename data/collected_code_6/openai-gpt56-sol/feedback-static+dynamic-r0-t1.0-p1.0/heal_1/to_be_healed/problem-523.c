#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static bool meets_requirements(const char *string, size_t required_length)
{
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    size_t length = 0;

    if (string == NULL) {
        return false;
    }

    for (const unsigned char *p = (const unsigned char *)string; *p != '\0'; ++p) {
        ++length;
        has_upper = has_upper || isupper(*p) != 0;
        has_lower = has_lower || islower(*p) != 0;
        has_digit = has_digit || isdigit(*p) != 0;
    }

    return length == required_length && has_upper && has_lower && has_digit;
}

int main(void)
{
    enum { BUFFER_SIZE = 256 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[BUFFER_SIZE];
    size_t required_length;

    if (printf("Enter the required length: ") < 0) {
        return 1;
    }

    if (scanf("%zu", &required_length) != 1) {
        fprintf(stderr, "Invalid length.\n");
        return 1;
    }

    int ch;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    if (printf("Enter the string: ") < 0) {
        return 1;
    }

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Failed to read the string.\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_length = strlen(input);

    if (input_length > 0 && input[input_length - 1] == '\n') {
        input[input_length - 1] = '\0';
    } else if (!feof(stdin)) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        fprintf(stderr, "Input is too long.\n");
        return 1;
    }

    if (meets_requirements(input, required_length)) {
        if (printf("The string meets all requirements.\n") < 0) {
            return 1;
        }
    } else {
        if (printf("The string does not meet all requirements.\n") < 0) {
            return 1;
        }
    }

    return 0;
}