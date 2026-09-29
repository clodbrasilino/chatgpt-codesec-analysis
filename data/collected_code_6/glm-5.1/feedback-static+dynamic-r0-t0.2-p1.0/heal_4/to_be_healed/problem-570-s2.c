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
        if (list[i] != NULL && !contains_substring(list[i], substr)) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(list[i]) + 1;
            result[j] = (char *)malloc(len * sizeof(char));
            if (result[j] == NULL) {
                for (size_t k = 0; k < j; k++) {
                    free(result[k]);
                }
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(result[j], list[i], len);
            result[j][len - 1] = '\0';
            j++;
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

    return result;
}

int main(void) {
    char *words[] = {
        "Red &",
        "Orange+",
        "Green",
        "Orange",
        "White"
    };
    size_t word_count = sizeof(words) / sizeof(words[0]);
    const char *filter = "an";

    size_t out_count = 0;
    char **filtered = remove_words(words, word_count, filter, &out_count);

    if (filtered == NULL) {
        if (out_count == 0) {
            return EXIT_SUCCESS;
        }
        return EXIT_FAILURE;
    }

    printf("[");
    for (size_t i = 0; i < out_count; i++) {
        printf("'%s'", filtered[i]);
        if (i < out_count - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    for (size_t i = 0; i < out_count; i++) {
        free(filtered[i]);
    }
    free(filtered);

    return EXIT_SUCCESS;
}