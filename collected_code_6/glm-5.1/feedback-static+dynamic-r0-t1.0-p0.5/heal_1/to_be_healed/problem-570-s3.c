#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contains_substring(const char *str, const char *substr) {
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
        if (list[i] != NULL && contains_substring(list[i], substr)) {
            free(list[i]);
            list[i] = NULL;
        } else {
            result[j++] = list[i];
        }
    }

    *out_count = j;

    char **shrunk = (char **)realloc(result, j * sizeof(char *));
    if (shrunk != NULL || j == 0) {
        if (shrunk != NULL) {
            result = shrunk;
        }
    }

    free(list);

    return result;
}

int main(void) {
    size_t count = 5;
    char **list = (char **)malloc(count * sizeof(char *));
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    list[0] = strdup("apple");
    list[1] = strdup("banana");
    list[2] = strdup("cherry");
    list[3] = strdup("date");
    list[4] = strdup("grape");

    if (list[0] == NULL || list[1] == NULL || list[2] == NULL || list[3] == NULL || list[4] == NULL) {
        for (size_t i = 0; i < count; i++) {
            free(list[i]);
        }
        free(list);
        return EXIT_FAILURE;
    }

    size_t out_count = 0;
    char **new_list = remove_words(list, count, "an", &out_count);

    if (new_list == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < out_count; i++) {
        printf("%s\n", new_list[i]);
        free(new_list[i]);
    }

    free(new_list);

    return EXIT_SUCCESS;
}