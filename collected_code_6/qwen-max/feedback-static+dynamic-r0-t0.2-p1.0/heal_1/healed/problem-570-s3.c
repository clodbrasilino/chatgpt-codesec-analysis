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

    char **result = (char **)malloc((new_count + 1) * sizeof(char *));
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
    result[index] = NULL;

    return result;
}

void free_strings(char **strings) {
    if (strings != NULL) {
        for (int i = 0; strings[i] != NULL; ++i) {
            free(strings[i]);
        }
        free(strings);
    }
}

int main() {
    char *strings[] = {"hello", "world", "test", "example", "remove"};
    int count = 5;
    const char *to_remove = "e";

    char **filtered = filter_strings(strings, count, to_remove);
    if (filtered != NULL) {
        for (int i = 0; filtered[i] != NULL; ++i) {
            printf("%s\n", filtered[i]);
        }
        free_strings(filtered);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
    }

    return 0;
}