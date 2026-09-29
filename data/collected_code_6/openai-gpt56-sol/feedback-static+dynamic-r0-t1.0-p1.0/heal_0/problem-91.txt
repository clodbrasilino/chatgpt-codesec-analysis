#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

static bool list_contains_substring(const char *const strings[],
                                    size_t count,
                                    const char *substring)
{
    if (strings == NULL || substring == NULL) {
        return false;
    }

    for (size_t i = 0; i < count; ++i) {
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
        "dragon fruit"
    };
    const char *substring = "fruit";
    const size_t value_count = sizeof(values) / sizeof(values[0]);

    if (list_contains_substring(values, value_count, substring)) {
        if (printf("Substring found\n") < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("Substring not found\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}