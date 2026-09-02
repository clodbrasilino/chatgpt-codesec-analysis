#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **filter_strings(char *strings[], int count, const char *to_remove) {
    int new_count = 0;
    for (int i = 0; i < count; ++i) {
        if (strstr(strings[i], to_remove) == NULL) {
            ++new_count;
        }
    }

    char **result = (char **)malloc(new_count * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < count; ++i) {
        if (strstr(strings[i], to_remove) == NULL) {
            result[index] = strdup(strings[i]);
            if (result[index] == NULL) {
                for (int j = 0; j < index; ++j) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            ++index;
        }
    }

    return result;
}

void free_strings(char **strings, int count) {
    for (int i = 0; i < count; ++i) {
        free(strings[i]);
    }
    free(strings);
}

int main() {
    char *strings[] = {"hello", "world", "test", "example", "remove"};
    int count = 5;
    const char *to_remove = "e";

    char **filtered = filter_strings(strings, count, to_remove);
    if (filtered != NULL) {
        int new_count = 0;
        /* Possible weaknesses found:
         * ASan: heap-buffer-overflow
         */
        for (int i = 0; filtered[i] != NULL; ++i) {
            printf("%s\n", filtered[i]);
            ++new_count;
        }
        free_strings(filtered, new_count);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
    }

    return 0;
}