#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **filter_strings(char **strings, int count, const char *to_remove) {
    int new_count = 0;
    for (int i = 0; i < count; ++i) {
        if (strstr(strings[i], to_remove) == NULL) {
            ++new_count;
        } else {
            /* Possible weaknesses found:
             * ASan: BUS
             */
            free(strings[i]);
            strings[i] = NULL;
        }
    }

    char **filtered = (char **)malloc(new_count * sizeof(char *));
    if (filtered == NULL) {
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < count; ++i) {
        if (strings[i] != NULL) {
            filtered[index++] = strings[i];
        }
    }

    return filtered;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *strings[5] = {"hello", "world", "test", "example", "remove"};
    int count = 5;
    const char *to_remove = "e";

    char **filtered = filter_strings(strings, count, to_remove);
    if (filtered != NULL) {
        for (int i = 0; i < count - 1; ++i) {
            if (filtered[i] != NULL) {
                printf("%s\n", filtered[i]);
            }
        }
        free(filtered);
    }

    return 0;
}