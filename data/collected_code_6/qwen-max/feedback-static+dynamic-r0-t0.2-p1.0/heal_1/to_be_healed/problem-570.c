#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **filter_strings(char **strings, int *count, const char *to_remove) {
    int new_count = 0;
    for (int i = 0; i < *count; ++i) {
        if (strstr(strings[i], to_remove) == NULL) {
            ++new_count;
        }
    }

    char **filtered = (char **)malloc(new_count * sizeof(char *));
    if (filtered == NULL) {
        return NULL;
    }

    int j = 0;
    for (int i = 0; i < *count; ++i) {
        if (strstr(strings[i], to_remove) == NULL) {
            filtered[j] = strings[i];
            ++j;
        } else {
            /* Possible weaknesses found:
             * ASan: BUS
             */
            free(strings[i]);
        }
    }

    *count = new_count;
    return filtered;
}

int main() {
    char *strings[] = {"hello", "world", "test", "example", "remove"};
    int count = 5;
    const char *to_remove = "e";

    char **filtered = filter_strings(strings, &count, to_remove);
    if (filtered == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < count; ++i) {
        printf("%s\n", filtered[i]);
    }

    for (int i = 0; i < count; ++i) {
        free(filtered[i]);
    }
    free(filtered);

    return 0;
}