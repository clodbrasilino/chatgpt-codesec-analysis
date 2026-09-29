#include <stdio.h>
#include <string.h>
#include <stdbool.h>

static bool is_palindrome(const char *string)
{
    size_t left = 0;
    size_t right;

    if (string == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    right = strlen(string);

    while (left < right) {
        if (string[left] != string[right - 1]) {
            return false;
        }

        ++left;
        --right;
    }

    return true;
}

static void print_palindromes(const char *const strings[], size_t count)
{
    size_t i;

    if (strings == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        if (strings[i] != NULL && is_palindrome(strings[i])) {
            if (printf("%s\n", strings[i]) < 0) {
                return;
            }
        }
    }
}

int main(void)
{
    const char *const strings[] = {
        "level",
        "example",
        "radar",
        "world",
        "madam",
        "civic",
        "programming"
    };
    const size_t count = sizeof(strings) / sizeof(strings[0]);

    print_palindromes(strings, count);

    if (ferror(stdout) != 0) {
        return 1;
    }

    return 0;
}