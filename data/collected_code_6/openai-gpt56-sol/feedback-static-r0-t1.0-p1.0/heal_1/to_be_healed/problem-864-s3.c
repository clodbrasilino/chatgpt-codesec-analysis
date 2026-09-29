#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

static bool is_palindrome(const char *text)
{
    size_t left = 0;
    size_t right;

    if (text == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    right = strlen(text);

    while (left < right) {
        if (text[left] != text[right - 1]) {
            return false;
        }

        ++left;
        --right;
    }

    return true;
}

static bool find_palindromes(const char *const strings[], size_t count)
{
    size_t i;

    if (strings == NULL && count != 0U) {
        return false;
    }

    for (i = 0; i < count; ++i) {
        if (strings[i] == NULL) {
            return false;
        }

        if (is_palindrome(strings[i])) {
            if (printf("%s\n", strings[i]) < 0) {
                return false;
            }
        }
    }

    return true;
}

int main(void)
{
    static const char *const strings[] = {
        "level",
        "world",
        "radar",
        "example",
        "madam",
        "civic"
    };
    const size_t count = sizeof(strings) / sizeof(strings[0]);

    if (!find_palindromes(strings, count)) {
        fputs("Failed to process the string list.\n", stderr);
        return 1;
    }

    if (fflush(stdout) == EOF) {
        fputs("Failed to flush standard output.\n", stderr);
        return 1;
    }

    return 0;
}