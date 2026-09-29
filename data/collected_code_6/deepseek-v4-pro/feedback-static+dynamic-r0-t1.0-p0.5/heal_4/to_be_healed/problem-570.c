#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got ["Red color","Orange#","Green"]
  *  test case 2 failed: expected ['Red &', 'Orange+', 'Green', 'Orange', 'White'], got ["Red &"]
  *  test case 1 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got null
  */

char **remove_words(char **words, int word_count, const char *filter, int *new_count) {
    if (words == NULL || filter == NULL || new_count == NULL || word_count <= 0) {
        if (new_count != NULL) {
            *new_count = 0;
        }
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t filter_len = strlen(filter);
    if (filter_len == 0) {
        *new_count = 0;
        return NULL;
    }

    char **result = (char **)malloc((size_t)word_count * sizeof(char *));
    if (result == NULL) {
        *new_count = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < word_count; i++) {
        if (words[i] != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t word_len = strlen(words[i]);
            /* Possible weaknesses found:
             *  Assuming that condition 'word_len>0' is not redundant
             */
            if (word_len > 0) {
                int found = 0;
                if (word_len >= filter_len) {
                    for (size_t j = 0; j <= word_len - filter_len; j++) {
                        if (strncmp(words[i] + j, filter, filter_len) == 0) {
                            found = 1;
                            break;
                        }
                    }
                }
                if (!found) {
                    result[count] = (char *)malloc((word_len + 1) * sizeof(char));
                    /* Possible weaknesses found:
                     *  Assuming condition is false
                     */
                    if (result[count] == NULL) {
                        for (int j = 0; j < count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        *new_count = 0;
                        return NULL;
                    }
                    /* Possible weaknesses found:
                     *  Condition 'word_len>0' is always true [knownConditionTrueFalse]
                     *  Condition 'word_len>0' is always true
                     */
                    if (word_len > 0) {
                        /* Possible weaknesses found:
                         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                         */
                        memcpy(result[count], words[i], word_len);
                    }
                    result[count][word_len] = '\0';
                    count++;
                }
            }
        }
    }

    if (count == 0) {
        free(result);
        *new_count = 0;
        return NULL;
    }

    char **final_result = (char **)realloc(result, (size_t)count * sizeof(char *));
    if (final_result == NULL) {
        for (int j = 0; j < count; j++) {
            free(result[j]);
        }
        free(result);
        *new_count = 0;
        return NULL;
    }

    *new_count = count;
    return final_result;
}

void free_words(char **words, int count) {
    if (words == NULL) {
        return;
    }
    for (int i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

int main(void) {
    char *words[] = {
        "Red",
        "",
        "Green",
        "Orange",
        "White"
    };
    int word_count = (int)(sizeof(words) / sizeof(words[0]));
    int new_count = 0;

    char **filtered = remove_words(words, word_count, "a", &new_count);

    if (filtered != NULL) {
        printf("Filtered words (%d):\n", new_count);
        for (int i = 0; i < new_count; i++) {
            printf("%s\n", filtered[i]);
        }
        free_words(filtered, new_count);
    } else {
        printf("No words remained after filtering.\n");
    }

    return 0;
}