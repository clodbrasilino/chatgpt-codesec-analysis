#include <stdio.h>

#define STRING_CAPACITY 1024U

static int first_and_last_equal(const char *string, size_t length)
{
    return string != NULL &&
           length > 0U &&
           string[0] == string[length - 1U];
}

static int read_line(char *buffer, size_t capacity, size_t *length)
{
    size_t count = 0U;
    int character;

    if (buffer == NULL || length == NULL || capacity == 0U) {
        return 0;
    }

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (count + 1U >= capacity) {
            while (character != '\n' && character != EOF) {
                character = fgetc(stdin);
            }

            buffer[0] = '\0';
            *length = 0U;
            return 0;
        }

        buffer[count++] = (char)character;
    }

    if (character == EOF && count == 0U) {
        buffer[0] = '\0';
        *length = 0U;
        return 0;
    }

    buffer[count] = '\0';
    *length = count;
    return 1;
}

int main(void)
{
    char string[STRING_CAPACITY];
    size_t length;

    if (!read_line(string, sizeof string, &length)) {
        return 1;
    }

    puts(first_and_last_equal(string, length) ? "Equal" : "Not equal");
    return 0;
}