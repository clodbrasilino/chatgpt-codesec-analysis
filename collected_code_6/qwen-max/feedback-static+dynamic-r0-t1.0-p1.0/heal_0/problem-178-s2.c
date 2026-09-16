#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool search_literals(const char *haystack, const char **needles, size_t needle_count) {
    for (size_t i = 0; i < needle_count; ++i) {
        if (strstr(haystack, needles[i]) != NULL) {
            return true;
        }
    }
    return false;
}

int main() {
    const char *haystack = "This is a test string with some literals";
    const char *needles[] = {"test", "literals", "missing"};
    size_t needle_count = sizeof(needles) / sizeof(needles[0]);

    if (search_literals(haystack, needles, needle_count)) {
        printf("At least one of the literals was found in the string.\n");
    } else {
        printf("None of the literals were found in the string.\n");
    }

    return 0;
}