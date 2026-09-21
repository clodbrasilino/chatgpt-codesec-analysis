#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define INPUT_CAPACITY 1024U

static bool has_two_alternating_characters(const char *str, size_t length)
{
    if (str == NULL || length < 2U || str[0] == str[1]) {
        return false;
    }

    for (size_t i = 2U; i < length; ++i) {
        if (str[i] != str[i % 2U]) {
            return false;
        }
    }

    return true;
}

static bool discard_remaining_input(void)
{
    int character;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = getchar();
    } while (character != '\n' && character != EOF);

    return character == '\n' || (character == EOF && !ferror(stdin));
}

static bool read_line(char *buffer, size_t capacity, size_t *length)
{
    if (buffer == NULL || length == NULL || capacity < 2U) {
        return false;
    }

    *length = 0U;

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return false;
    }

    size_t index = 0U;

    while (index < capacity && buffer[index] != '\0' &&
           buffer[index] != '\n') {
        ++index;
    }

    if (index < capacity && buffer[index] == '\n') {
        buffer[index] = '\0';
        *length = index;
        return true;
    }

    if (index < capacity && buffer[index] == '\0' && feof(stdin)) {
        *length = index;
        return true;
    }

    buffer[capacity - 1U] = '\0';

    if (!discard_remaining_input()) {
        return false;
    }

    return false;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_CAPACITY + 1U];
    size_t length;

    if (!read_line(input, sizeof input, &length)) {
        return 1;
    }

    puts(has_two_alternating_characters(input, length) ? "Yes" : "No");

    return 0;
}