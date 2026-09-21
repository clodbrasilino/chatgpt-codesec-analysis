#include <stdio.h>
#include <string.h>
#include <stdbool.h>

static bool is_palindrome(const char *string, size_t length)
{
    size_t left = 0;
    size_t right = length;

    if (string == NULL) {
        return false;
    }

    while (left < right) {
        if (string[left] != string[right - 1]) {
            return false;
        }

        ++left;
        --right;
    }

    return true;
}

static void print_palindromes(const char *const strings[],
                              const size_t lengths[],
                              size_t count)
{
    size_t i;

    if (strings == NULL || lengths == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        if (strings[i] != NULL && is_palindrome(strings[i], lengths[i])) {
            if (printf("%.*s\n", (int)lengths[i], strings[i]) < 0) {
                return;
            }
        }
    }
}

int main(void)
{
    static const char level[] = "level";
    static const char example[] = "example";
    static const char radar[] = "radar";
    static const char world[] = "world";
    static const char madam[] = "madam";
    static const char civic[] = "civic";
    static const char programming[] = "programming";

    const char *const strings[] = {
        level,
        example,
        radar,
        world,
        madam,
        civic,
        programming
    };

    const size_t lengths[] = {
        sizeof(level) - 1,
        sizeof(example) - 1,
        sizeof(radar) - 1,
        sizeof(world) - 1,
        sizeof(madam) - 1,
        sizeof(civic) - 1,
        sizeof(programming) - 1
    };

    const size_t count = sizeof(strings) / sizeof(strings[0]);

    print_palindromes(strings, lengths, count);

    return ferror(stdout) ? 1 : 0;
}