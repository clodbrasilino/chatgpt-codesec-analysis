#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_INPUT_LENGTH 256
#define MAX_FLUSH_COUNT ((size_t)MAX_INPUT_LENGTH * 16)

static bool is_valid_password(const char *str, size_t required_length)
{
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    size_t length;
    size_t i;

    if (str == NULL) {
        return false;
    }

    length = strnlen(str, MAX_INPUT_LENGTH);

    if (length >= MAX_INPUT_LENGTH || length != required_length) {
        return false;
    }

    for (i = 0; i < length; i++) {
        unsigned char c = (unsigned char)str[i];

        if (isupper(c)) {
            has_upper = true;
        } else if (islower(c)) {
            has_lower = true;
        } else if (isdigit(c)) {
            has_digit = true;
        }
    }

    return (has_upper && has_lower && has_digit);
}

static void flush_stdin(void)
{
    size_t count = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    while (count < MAX_FLUSH_COUNT) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        if (ch == '\n' || ch == EOF) {
            break;
        }
        count++;
    }
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT_LENGTH];
    size_t required_length = 8;
    size_t input_length;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter a string to validate (required length %zu): ", required_length);

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    input_length = strnlen(buffer, sizeof(buffer));

    if (input_length > 0 && buffer[input_length - 1] == '\n') {
        buffer[input_length - 1] = '\0';
    } else {
        flush_stdin();
    }

    if (is_valid_password(buffer, required_length)) {
        printf("The string is valid.\n");
    } else {
        printf("The string is invalid.\n");
    }

    return EXIT_SUCCESS;
}