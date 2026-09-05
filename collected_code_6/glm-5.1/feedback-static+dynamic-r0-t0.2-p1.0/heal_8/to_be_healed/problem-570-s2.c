#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contains_substring(const char *str, const char *substr) {
    if (str == NULL || substr == NULL) return 0;
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
        if (list[i] != NULL && !contains_substring(list[i], substr)) {
            result[j] = (char *)list[i];
            j++;
        }
    }

    *out_count = j;

    if (j == 0) {
        free(result);
        return NULL;
    }

    char **shrunk = (char **)realloc(result, j * sizeof(char *));
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    char *words[] = {
        "Red",
        "",
        "Green",
        "Orange",
        "White"
    };
    size_t word_count = sizeof(words) / sizeof(words[0]);
    const char *filter = "an";

    size_t out_count = 0;
    char **filtered = remove_words(words, word_count, filter, &out_count);

    printf("[");
    for (size_t i = 0; i < out_count; i++) {
        printf("'%s'", filtered[i]);
        if (i < out_count - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    if (filtered != NULL) {
        free(filtered);
    }

    return EXIT_SUCCESS;
}