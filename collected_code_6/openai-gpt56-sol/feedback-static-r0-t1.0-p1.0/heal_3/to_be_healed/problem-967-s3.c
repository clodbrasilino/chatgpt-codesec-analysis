#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static bool contains_all_vowels(const char *string)
{
    unsigned int found = 0;

    if (string == NULL) {
        return false;
    }

    while (*string != '\0') {
        switch (tolower((unsigned char)*string)) {
        case 'a':
            found |= 1U << 0;
            break;
        case 'e':
            found |= 1U << 1;
            break;
        case 'i':
            found |= 1U << 2;
            break;
        case 'o':
            found |= 1U << 3;
            break;
        case 'u':
            found |= 1U << 4;
            break;
        default:
            break;
        }

        if (found == 0x1FU) {
            return true;
        }

        ++string;
    }

    return false;
}

static char *read_line(FILE *stream)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != EOF && character != '\n') {
        if (length == SIZE_MAX - 1) {
            free(input);
            return NULL;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    return NULL;
                }
                new_capacity = capacity * 2;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return NULL;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (ferror(stream) || (length == 0 && character == EOF)) {
        free(input);
        return NULL;
    }

    if (length == capacity) {
        char *resized = realloc(input, length + 1);

        if (resized == NULL) {
            free(input);
            return NULL;
        }

        input = resized;
    }

    input[length] = '\0';
    return input;
}

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    puts(contains_all_vowels(input) ? "Accepted" : "Rejected");
    free(input);

    return ferror(stdout) ? EXIT_FAILURE : EXIT_SUCCESS;
}