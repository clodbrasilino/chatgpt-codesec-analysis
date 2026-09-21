#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 4096U

static int is_palindrome(const char *string, size_t capacity)
{
    const char *terminator;
    size_t left = 0U;
    size_t right;

    if (string == NULL || capacity == 0U) {
        return 0;
    }

    terminator = memchr(string, '\0', capacity);
    if (terminator == NULL) {
        return 0;
    }

    right = (size_t)(terminator - string);

    while (left < right) {
        --right;
        if (string[left] != string[right]) {
            return 0;
        }
        ++left;
    }

    return 1;
}

static int print_palindromes(const char *const strings[], size_t count)
{
    size_t i;

    if (strings == NULL && count != 0U) {
        return -1;
    }

    for (i = 0U; i < count; ++i) {
        if (strings[i] == NULL) {
            return -1;
        }

        if (is_palindrome(strings[i], MAX_STRING_LENGTH) != 0) {
            if (printf("%s\n", strings[i]) < 0) {
                return -1;
            }
        }
    }

    return 0;
}

int main(void)
{
    const char *const strings[] = {
        "level",
        "hello",
        "radar",
        "world",
        "deified",
        "computer",
        "",
        "a"
    };
    const size_t count = sizeof(strings) / sizeof(strings[0]);

    if (print_palindromes(strings, count) != 0) {
        (void)fprintf(stderr, "Failed to process the string list.\n");
        return 1;
    }

    return 0;
}