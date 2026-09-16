#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contains_substring(const char *str, const char *substr) {
    if (str == NULL || substr == NULL) return 0;
    if (substr[0] == '\0') return 1;
    return strstr(str, substr) != NULL;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['Red &', 'Orange+', 'Green', 'Orange', 'White'], got <no output>
  *  test case 1 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got <no output>
  *  test case 0 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got <no output>
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
        if (list[i] == NULL || !contains_substring(list[i], substr)) {
            if (list[i] != NULL) {
                result[j] = strdup(list[i]);
                if (result[j] != NULL) {
                    j++;
                }
            } else {
                result[j] = NULL;
                j++;
            }
        }
    }

    *out_count = j;

    for (size_t i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);

    if (j == 0) {
        free(result);
        return NULL;
    }

    char **trimmed_result = (char **)realloc(result, j * sizeof(char *));
    if (trimmed_result != NULL) {
        return trimmed_result;
    }
    
    return result;
}

int main(void) {
    size_t capacity = 5;
    char **list = (char **)malloc(capacity * sizeof(char *));
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    list[0] = strdup("Red &");
    list[1] = NULL;
    list[2] = strdup("Green");
    list[3] = strdup("Orange");
    list[4] = strdup("White");

    if (list[0] == NULL || list[2] == NULL || list[3] == NULL || list[4] == NULL) {
        for (size_t i = 0; i < capacity; i++) {
            free(list[i]);
        }
        free(list);
        return EXIT_FAILURE;
    }

    size_t count = capacity;
    size_t out_count = 0;

    char **new_list = remove_words(list, count, "an", &out_count);

    if (new_list == NULL && out_count > 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < out_count; i++) {
        if (new_list[i] != NULL) {
            printf("%s\n", new_list[i]);
        } else {
            printf("\n");
        }
    }

    for (size_t i = 0; i < out_count; i++) {
        free(new_list[i]);
    }

    if (new_list != NULL) {
        free(new_list);
    }

    return EXIT_SUCCESS;
}