#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int find_first_repeated_character(const char *str, unsigned char *result)
{
    unsigned char *seen;

    if (str == NULL || result == NULL) {
        return -1;
    }

    seen = calloc((size_t)UCHAR_MAX + 1U, sizeof(*seen));
    if (seen == NULL) {
        return -2;
    }

    while (*str != '\0') {
        unsigned char ch = (unsigned char)*str;

        if (seen[ch] != 0U) {
            *result = ch;
            free(seen);
            return 1;
        }

        seen[ch] = 1U;
        ++str;
    }

    free(seen);
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    unsigned char repeated;
    int status;
    int ch;

    while ((ch = fgetc(stdin)) != EOF) {
        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > ((size_t)-1) / 2U) {
                    free(input);
                    fprintf(stderr, "Input is too large.\n");
                    return 1;
                }
                new_capacity = capacity * 2U;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fprintf(stderr, "Failed to allocate memory.\n");
                return 1;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;

        if (ch == '\n') {
            break;
        }
    }

    if (ferror(stdin)) {
        free(input);
        fprintf(stderr, "Failed to read input.\n");
        return 1;
    }

    if (length == 0U && ch == EOF) {
        free(input);
        return 0;
    }

    input[length] = '\0';

    status = find_first_repeated_character(input, &repeated);
    free(input);

    if (status == -1) {
        fprintf(stderr, "Invalid argument.\n");
        return 1;
    }

    if (status == -2) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return 1;
    }

    if (status == 1) {
        printf("%c\n", (int)repeated);
    } else {
        printf("No repeated character found.\n");
    }

    return 0;
}