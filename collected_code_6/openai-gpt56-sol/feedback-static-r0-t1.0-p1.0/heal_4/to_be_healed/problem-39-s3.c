#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static bool can_rearrange_without_adjacent_duplicates(
    const unsigned char *str,
    size_t length)
{
    size_t frequencies[256] = {0};
    size_t max_frequency = 0;

    if (str == NULL) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        size_t frequency = ++frequencies[str[i]];

        if (frequency > max_frequency) {
            max_frequency = frequency;
        }
    }

    return max_frequency <= length / 2U + length % 2U;
}

static unsigned char *read_line(size_t *length)
{
    unsigned char *buffer = NULL;
    size_t capacity = 0;
    size_t used = 0;
    int character;

    if (length == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (used == capacity) {
            size_t new_capacity = capacity == 0U ? 128U : capacity * 2U;

            if (new_capacity < capacity ||
                new_capacity > SIZE_MAX / sizeof(*buffer)) {
                free(buffer);
                return NULL;
            }

            unsigned char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[used++] = (unsigned char)character;
    }

    if (ferror(stdin)) {
        free(buffer);
        return NULL;
    }

    if (character == EOF && used == 0U) {
        free(buffer);
        *length = 0U;
        return NULL;
    }

    if (used > 0U && buffer[used - 1U] == '\r') {
        --used;
    }

    if (used == 0U) {
        free(buffer);
        buffer = malloc(1U);

        if (buffer == NULL) {
            return NULL;
        }
    }

    *length = used;
    return buffer;
}

int main(void)
{
    size_t length = 0;
    unsigned char *input = read_line(&length);

    if (input == NULL) {
        return feof(stdin) && !ferror(stdin) ? 0 : 1;
    }

    puts(can_rearrange_without_adjacent_duplicates(input, length)
             ? "true"
             : "false");

    free(input);
    return 0;
}