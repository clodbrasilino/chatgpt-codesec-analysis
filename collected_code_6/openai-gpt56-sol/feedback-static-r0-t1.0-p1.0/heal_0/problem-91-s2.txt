#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

static bool list_contains_substring(const char *const strings[],
                                    size_t count,
                                    const char *substring)
{
    size_t i;

    if (strings == NULL || substring == NULL) {
        return false;
    }

    for (i = 0U; i < count; ++i) {
        if (strings[i] != NULL && strstr(strings[i], substring) != NULL) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    static const char *const values[] = {
        "apple",
        "banana",
        "cherry",
        "date"
    };
    const char *substring = "nan";
    const size_t count = sizeof(values) / sizeof(values[0]);

    if (list_contains_substring(values, count, substring)) {
        if (printf("\"%s\" is present in the list.\n", substring) < 0) {
            return 1;
        }
    } else {
        if (printf("\"%s\" is not present in the list.\n", substring) < 0) {
            return 1;
        }
    }

    return 0;
}