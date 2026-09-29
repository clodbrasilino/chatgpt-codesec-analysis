#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contains_substring(const char *str, const char *substr) {
    return strstr(str, substr) != NULL;
}

char **remove_words(char **list, size_t count, const char *substr, size_t *out_count) {
    if (list == NULL || substr == NULL || out_count == NULL) {
        return NULL;
    }

    char **result = (char **)malloc(count * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL && contains_substring(list[i], substr)) {
            free(list[i]);
        } else {
            result[j++] = list[i];
        }
    }

    *out_count = j;

    char **shrunk = (char **)realloc(result, j * sizeof(char *));
    if (shrunk != NULL) {
        result = shrunk;
    } else if (j == 0) {
        free(result);
        result = NULL;
    }

    free(list);

    return result;
}

int main(void) {
    char **list = (char **)malloc(5 * sizeof(char *));
    if (list == NULL) {
        return 1;
    }

    list[0] = strdup("Red &");
    list[1] = strdup("Orange+");
    list[2] = strdup("Green");
    list[3] = strdup("Orange");
    list[4] = strdup("White");

    if (list[0] == NULL || list[1] == NULL || list[2] == NULL || list[3] == NULL || list[4] == NULL) {
        for (int i = 0; i < 5; i++) {
            if (list[i] != NULL) {
                free(list[i]);
            }
        }
        free(list);
        return 1;
    }

    size_t out_count = 0;
    char **new_list = remove_words(list, 5, "an", &out_count);

    if (new_list == NULL && out_count == 0) {
        return 0;
    }

    if (new_list == NULL) {
        return 1;
    }

    for (size_t i = 0; i < out_count; i++) {
        printf("%s\n", new_list[i]);
        free(new_list[i]);
    }

    free(new_list);

    return 0;
}