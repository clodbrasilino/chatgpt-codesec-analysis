#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

static bool is_palindrome(const char *text, size_t length)
{
    size_t left = 0;
    size_t right = length;

    if (text == NULL) {
        return false;
    }

    while (left < right) {
        if (text[left] != text[right - 1U]) {
            return false;
        }

        ++left;
        --right;
    }

    return true;
}

static bool find_palindromes(const char *const strings[],
                             const size_t lengths[],
                             size_t count)
{
    size_t i;

    if ((strings == NULL || lengths == NULL) && count != 0U) {
        return false;
    }

    for (i = 0; i < count; ++i) {
        if (strings[i] == NULL) {
            return false;
        }

        if (is_palindrome(strings[i], lengths[i])) {
            if (fwrite(strings[i], 1U, lengths[i], stdout) != lengths[i] ||
                fputc('\n', stdout) == EOF) {
                return false;
            }
        }
    }

    return true;
}

int main(void)
{
    static const char level[] = "level";
    static const char world[] = "world";
    static const char radar[] = "radar";
    static const char example[] = "example";
    static const char madam[] = "madam";
    static const char civic[] = "civic";

    static const char *const strings[] = {
        level,
        world,
        radar,
        example,
        madam,
        civic
    };

    static const size_t lengths[] = {
        sizeof(level) - 1U,
        sizeof(world) - 1U,
        sizeof(radar) - 1U,
        sizeof(example) - 1U,
        sizeof(madam) - 1U,
        sizeof(civic) - 1U
    };

    const size_t count = sizeof(strings) / sizeof(strings[0]);

    if (!find_palindromes(strings, lengths, count)) {
        fputs("Failed to process the string list.\n", stderr);
        return 1;
    }

    if (fflush(stdout) == EOF) {
        fputs("Failed to flush standard output.\n", stderr);
        return 1;
    }

    return 0;
}