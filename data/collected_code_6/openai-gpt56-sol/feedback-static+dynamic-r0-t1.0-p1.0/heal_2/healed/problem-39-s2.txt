#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 128U

static bool can_rearrange_without_adjacent_duplicates(
    const char *string,
    size_t length)
{
    size_t frequencies[256] = {0};
    size_t maximum = 0;

    if (string == NULL) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = (unsigned char)string[i];

        ++frequencies[character];
        if (frequencies[character] > maximum) {
            maximum = frequencies[character];
        }
    }

    return maximum <= length / 2U + length % 2U;
}

int main(void)
{
    char *input = malloc(INITIAL_CAPACITY);
    size_t capacity = INITIAL_CAPACITY;
    size_t length = 0;
    int character = EOF;

    if (input == NULL) {
        return 1;
    }

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length == capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(input);
                return 1;
            }

            new_capacity = capacity * 2U;
            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return 1;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin) || (character == EOF && length == 0U)) {
        free(input);
        return 1;
    }

    if (length > 0U && input[length - 1U] == '\r') {
        --length;
    }

    puts(can_rearrange_without_adjacent_duplicates(input, length)
             ? "true"
             : "false");

    free(input);
    return 0;
}