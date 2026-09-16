#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search_literals(const char *target, const char **literals, size_t literals_count) {
    if (!target || !literals || literals_count == 0) {
        return -1;
    }

    int found_count = 0;
    for (size_t i = 0; i < literals_count; ++i) {
        if (!literals[i]) {
            continue;
        }

        if (strstr(target, literals[i]) != NULL) {
            found_count++;
        }
    }

    return found_count;
}

int main(void) {
    const char *target_string = "The quick brown fox jumps over the lazy dog";
    const char *literals[] = {"fox", "cat", "dog", "bear"};
    size_t literals_count = sizeof(literals) / sizeof(literals[0]);

    int matches = search_literals(target_string, literals, literals_count);

    if (matches >= 0) {
        printf("Found %d literals in the string.\n", matches);
    } else {
        printf("Invalid input provided.\n");
    }

    return 0;
}