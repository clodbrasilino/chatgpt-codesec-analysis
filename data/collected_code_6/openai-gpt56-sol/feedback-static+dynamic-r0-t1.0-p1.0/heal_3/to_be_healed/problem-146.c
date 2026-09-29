#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int print_ascii_values(const char *string)
{
    const unsigned char *cursor = (const unsigned char *)string;

    if (cursor == NULL) {
        return -1;
    }

    while (*cursor != '\0') {
        if (printf("%u\n", (unsigned int)*cursor) < 0) {
            return -1;
        }
        ++cursor;
    }

    return 0;
}

int main(void)
{
    char *string;
    size_t length = 0;
    size_t capacity = 128;
    int character;
    int result = EXIT_SUCCESS;

    string = malloc(capacity);
    if (string == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length >= capacity - 1) {
            size_t new_capacity;
            char *temporary;

            if (capacity > SIZE_MAX / 2) {
                free(string);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2;
            temporary = realloc(string, new_capacity);
            if (temporary == NULL) {
                free(string);
                return EXIT_FAILURE;
            }

            string = temporary;
            capacity = new_capacity;
        }

        string[length++] = (char)(unsigned char)character;
    }

    if (ferror(stdin)) {
        perror("fgetc");
        free(string);
        return EXIT_FAILURE;
    }

    string[length] = '\0';

    if (print_ascii_values(string) != 0) {
        result = EXIT_FAILURE;
    }

    free(string);
    return result;
}