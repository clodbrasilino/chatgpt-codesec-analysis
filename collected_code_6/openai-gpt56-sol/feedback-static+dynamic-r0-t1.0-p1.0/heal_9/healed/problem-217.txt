#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BYTE_VALUES (UINT8_MAX + 1U)

int find_first_repeated_character(const unsigned char *data,
                                  size_t length,
                                  unsigned char *result)
{
    uint8_t seen[BYTE_VALUES] = {0};

    if (result == NULL || (data == NULL && length != 0U)) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char ch = data[i];

        if (seen[ch] != 0U) {
            *result = ch;
            return 1;
        }

        seen[ch] = 1U;
    }

    return 0;
}

int main(void)
{
    unsigned char *data = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int c;

    while ((c = getchar()) != EOF && c != '\n') {
        if (length == capacity) {
            size_t new_capacity;
            unsigned char *new_data;

            if (capacity == 0U) {
                new_capacity = 64U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(data);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2U;
            }

            new_data = realloc(data, new_capacity);
            if (new_data == NULL) {
                free(data);
                return EXIT_FAILURE;
            }

            data = new_data;
            capacity = new_capacity;
        }

        data[length++] = (unsigned char)c;
    }

    if (ferror(stdin) != 0) {
        free(data);
        return EXIT_FAILURE;
    }

    unsigned char repeated;
    int found = find_first_repeated_character(data, length, &repeated);

    free(data);

    if (found != 0) {
        if (putchar((int)repeated) == EOF || putchar('\n') == EOF) {
            return EXIT_FAILURE;
        }
    } else if (puts("No repeated character") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}