#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contains_substring(const char *str, const char *substr) {
    if (str == NULL || substr == NULL) return 0;
    return strstr(str, substr) != NULL;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got <no output>
  *  test case 1 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got <no output>
  *  test case 2 failed: expected ['Red &', 'Orange+', 'Green', 'Orange', 'White'], got <no output>
  */

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
        if (list[i] == NULL) {
            continue;
        }
        if (contains_substring(list[i], substr)) {
            free(list[i]);
        } else {
            result[j++] = list[i];
        }
    }

    *out_count = j;

    if (j > 0) {
        char **trimmed_result = (char **)realloc(result, j * sizeof(char *));
        if (trimmed_result != NULL) {
            result = trimmed_result;
        }
    } else {
        free(result);
        result = NULL;
    }

    free(list);

    return result;
}

int main(void) {
    size_t capacity = 6;
    char **list = (char **)malloc(capacity * sizeof(char *));
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    list[0] = strdup("Red");
    list[1] = strdup("");
    list[2] = strdup("Green");
    list[3] = strdup("Orange");
    list[4] = strdup("White");
    list[5] = strdup("Blue");

    if (list[0] == NULL || list[1] == NULL || list[2] == NULL ||
        list[3] == NULL || list[4] == NULL || list[5] == NULL) {
        for (size_t i = 0; i < capacity; i++) {
            free(list[i]);
        }
        free(list);
        return EXIT_FAILURE;
    }

    size_t count = capacity;
    size_t out_count = 0;

    char **new_list = remove_words(list, count, "an", &out_count);

    printf("[");
    if (new_list != NULL) {
        for (size_t i = 0; i < out_count; i++) {
            printf("'%s'", new_list[i]);
            if (i < out_count - 1) {
                printf(", ");
            }
        }
    }
    printf("]\n");

    if (new_list != NULL) {
        for (size_t i = 0; i < out_count; i++) {
            free(new_list[i]);
        }
        free(new_list);
    }

    return EXIT_SUCCESS;
}