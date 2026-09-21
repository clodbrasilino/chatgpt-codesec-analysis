#include <stdio.h>
#include <string.h>

static int is_palindrome(const char *string)
{
    size_t left = 0;
    size_t right;

    if (string == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    right = strlen(string);

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

    for (i = 0; i < count; ++i) {
        if (strings[i] == NULL) {
            return -1;
        }

        if (is_palindrome(strings[i])) {
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