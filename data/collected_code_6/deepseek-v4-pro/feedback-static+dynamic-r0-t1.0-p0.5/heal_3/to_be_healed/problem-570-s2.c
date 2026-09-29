#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got ["Red color","Orange#","Green"]
  *  test case 1 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got ["Red &","Orange+","Green"]
  *  test case 2 failed: expected ['Red &', 'Orange+', 'Green', 'Orange', 'White'], got null
  */

char **remove_words(char **words, int word_count, const char *filter, int *new_count) {
    /* Possible weaknesses found:
     *  Assuming condition 'word_count<=0' is false
     */
    if (words == NULL || filter == NULL || new_count == NULL || word_count <= 0) {
        if (new_count != NULL) *new_count = 0;
        return NULL;
    }

    char **result = (char **)malloc(word_count * sizeof(char *));
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (result == NULL) {
        *new_count = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < word_count; i++) {
        if (words[i] != NULL && strstr(words[i], filter) == NULL) {
            /* Possible weaknesses found:
             *  Condition 'word_count>0' is always true
             *  Condition 'word_count>0' is always true [knownConditionTrueFalse]
             */
            size_t len = strnlen(words[i], word_count > 0 ? (size_t)word_count * 256 : 256);
            result[count] = (char *)malloc((len + 1) * sizeof(char));
            if (result[count] == NULL) {
                for (int j = 0; j < count; j++) {
                    free(result[j]);
                }
                free(result);
                *new_count = 0;
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[count], words[i], len);
            result[count][len] = '\0';
            count++;
        }
    }

    if (count == 0) {
        free(result);
        *new_count = 0;
        return NULL;
    }

    char **final_result = (char **)realloc(result, count * sizeof(char *));
    if (final_result == NULL && count > 0) {
        for (int j = 0; j < count; j++) {
            free(result[j]);
        }
        free(result);
        *new_count = 0;
        return NULL;
    }

    *new_count = count;
    return final_result != NULL ? final_result : result;
}

int main(void) {
    char *words[] = {
        "apple",
        "banana",
        "cherry",
        "date",
        "elderberry",
        "fig",
        "grape"
    };
    int word_count = sizeof(words) / sizeof(words[0]);
    int new_count = 0;

    char **filtered = remove_words(words, word_count, "a", &new_count);

    if (filtered != NULL) {
        printf("Filtered words (%d):\n", new_count);
        for (int i = 0; i < new_count; i++) {
            printf("%s\n", filtered[i]);
            free(filtered[i]);
        }
        free(filtered);
    } else {
        printf("No words remained after filtering.\n");
    }

    return 0;
}