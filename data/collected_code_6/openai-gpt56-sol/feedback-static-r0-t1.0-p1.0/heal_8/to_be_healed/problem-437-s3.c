#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void remove_odd_characters(char *string)
{
    size_t read_index = 0U;
    size_t write_index = 0U;

    if (string == NULL) {
        return;
    }

    while (string[read_index] != '\0') {
        if ((read_index & 1U) == 0U) {
            string[write_index++] = string[read_index];
        }
        ++read_index;
    }

    string[write_index] = '\0';
}

int main(void)
{
    char *string;
    size_t capacity = 128U;
    size_t length = 0U;

    string = malloc(capacity);
    if (string == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        char *result;

        if (length + 1U >= capacity) {
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2U) {
                free(string);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2U;
            result = realloc(string, new_capacity);
            if (result == NULL) {
                free(string);
                return EXIT_FAILURE;
            }

            string = result;
            capacity = new_capacity;
        }

        result = fgets(string + length, (int)(capacity - length), stdin);
        if (result == NULL) {
            if (ferror(stdin)) {
                free(string);
                return EXIT_FAILURE;
            }
            break;
        }

        while (string[length] != '\0' && string[length] != '\n') {
            ++length;
        }

        if (string[length] == '\n') {
            /* Possible weaknesses found:
             *  string[length] is assigned
             */
            string[length] = '\0';
            break;
        }

        if (feof(stdin)) {
            break;
        }
    }

    /* Possible weaknesses found:
     *  Variable 'string[length]' is reassigned a value before the old one has been used. [redundantAssignment]
     *  string[length] is overwritten
     */
    string[length] = '\0';
    remove_odd_characters(string);

    if (puts(string) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}