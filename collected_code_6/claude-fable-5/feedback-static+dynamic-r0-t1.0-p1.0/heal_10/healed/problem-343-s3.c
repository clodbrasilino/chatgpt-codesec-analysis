#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE 256

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

int main(void)
{
    char buffer[BUFFER_SIZE];
    size_t digits = 0;
    size_t letters = 0;
    size_t len;

    printf("Enter a string: ");
    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    count_digits_letters(buffer, sizeof(buffer), &digits, &letters);

    printf("Digits: %zu\n", digits);
    printf("Letters: %zu\n", letters);

    return EXIT_SUCCESS;
}