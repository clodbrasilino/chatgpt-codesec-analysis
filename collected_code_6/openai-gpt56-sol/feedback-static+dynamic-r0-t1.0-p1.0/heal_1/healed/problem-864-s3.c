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

struct bounded_string {
    const char *text;
    size_t length;
};

static bool find_palindromes(const struct bounded_string strings[], size_t count)
{
    size_t i;

    if (strings == NULL && count != 0U) {
        return false;
    }

    for (i = 0; i < count; ++i) {
        if (strings[i].text == NULL) {
            return false;
        }

        if (is_palindrome(strings[i].text, strings[i].length)) {
            if (fwrite(strings[i].text, 1U, strings[i].length, stdout) !=
                    strings[i].length ||
                fputc('\n', stdout) == EOF) {
                return false;
            }
        }
    }

    return true;
}

int main(void)
{
    static const struct bounded_string strings[] = {
        {"level", sizeof("level") - 1U},
        {"world", sizeof("world") - 1U},
        {"radar", sizeof("radar") - 1U},
        {"example", sizeof("example") - 1U},
        {"madam", sizeof("madam") - 1U},
        {"civic", sizeof("civic") - 1U}
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