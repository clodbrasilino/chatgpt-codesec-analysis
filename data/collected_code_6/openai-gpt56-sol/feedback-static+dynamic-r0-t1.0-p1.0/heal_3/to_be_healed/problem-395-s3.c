#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int first_non_repeated_character(const char *str, unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    const unsigned char *current;

    if (str == NULL || result == NULL) {
        return 0;
    }

    current = (const unsigned char *)str;

    while (*current != '\0') {
        ++frequencies[*current];
        ++current;
    }

    current = (const unsigned char *)str;

    while (*current != '\0') {
        if (frequencies[*current] == 1) {
            *result = *current;
            return 1;
        }
        ++current;
    }

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 128;
    unsigned char result;
    int ch;

    input = malloc(capacity);
    if (input == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                fprintf(stderr, "Input is too long.\n");
                free(input);
                return 1;
            }

            new_capacity = capacity * 2;
            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                fprintf(stderr, "Failed to allocate memory.\n");
                free(input);
                return 1;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        fprintf(stderr, "Failed to read input.\n");
        free(input);
        return 1;
    }

    if (ch == EOF && length == 0) {
        fprintf(stderr, "No input provided.\n");
        free(input);
        return 1;
    }

    input[length] = '\0';

    if (first_non_repeated_character(input, &result)) {
        printf("%c\n", (int)result);
    } else {
        puts("No non-repeated character found.");
    }

    free(input);
    return 0;
}