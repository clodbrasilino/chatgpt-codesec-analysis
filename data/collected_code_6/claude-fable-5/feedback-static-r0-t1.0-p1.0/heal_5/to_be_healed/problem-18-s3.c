#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

void remove_chars(char *str, const char *mask);
static bool read_line(char *buffer, size_t size);

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

static bool read_line(char *buffer, size_t size)
{
    char *newline;

    if (buffer == NULL || size == 0) {
        return false;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return false;
    }

    buffer[size - 1] = '\0';

    newline = memchr(buffer, '\n', size);
    if (newline != NULL) {
        *newline = '\0';
    }

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char first[BUFFER_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char second[BUFFER_SIZE];

    printf("Enter the first string: ");
    if (!read_line(first, sizeof(first))) {
        fprintf(stderr, "Error reading first string\n");
        return EXIT_FAILURE;
    }

    printf("Enter the second string: ");
    if (!read_line(second, sizeof(second))) {
        fprintf(stderr, "Error reading second string\n");
        return EXIT_FAILURE;
    }

    remove_chars(first, second);

    printf("Result: %s\n", first);

    return EXIT_SUCCESS;
}