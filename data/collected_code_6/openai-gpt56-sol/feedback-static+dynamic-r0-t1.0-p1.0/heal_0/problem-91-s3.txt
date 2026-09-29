#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

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
    const char *const strings[] = {
        "apple",
        "banana",
        "cherry",
        "blueberry"
    };
    const char *substring = "berry";
    const size_t count = sizeof(strings) / sizeof(strings[0]);

    if (list_contains_substring(strings, count, substring)) {
        if (printf("Substring found.\n") < 0) {
            return 1;
        }
    } else {
        if (printf("Substring not found.\n") < 0) {
            return 1;
        }
    }

    return 0;
}