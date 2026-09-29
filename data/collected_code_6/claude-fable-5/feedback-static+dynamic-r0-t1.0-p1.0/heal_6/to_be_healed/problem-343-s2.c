#include <stdio.h>
#include <ctype.h>
#include <stddef.h>
#include <string.h>

#define INPUT_SIZE 256

void count_digits_letters(const char *str, size_t max_len, size_t *digits, size_t *letters)
{
    size_t i;

    if (str == NULL || digits == NULL || letters == NULL) {
        return;
    }

    *digits = 0;
    *letters = 0;

    for (i = 0; i < max_len && str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (isdigit(c)) {
            (*digits)++;
        } else if (isalpha(c)) {
            (*letters)++;
        }
    }
}

static void flush_stdin(void)
{
    int c;
    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];
    size_t digits = 0;
    size_t letters = 0;
    const char *newline;

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    input[sizeof(input) - 1] = '\0';

    newline = memchr(input, '\n', sizeof(input));
    if (newline != NULL) {
        size_t len = (size_t)(newline - input);
        input[len] = '\0';
    } else {
        flush_stdin();
    }

    count_digits_letters(input, sizeof(input), &digits, &letters);

    printf("Digits: %zu\n", digits);
    printf("Letters: %zu\n", letters);

    return 0;
}