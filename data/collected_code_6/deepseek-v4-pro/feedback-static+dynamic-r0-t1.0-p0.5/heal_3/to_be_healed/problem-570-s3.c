#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got ["Red color","Orange#","Green"]
  *  test case 1 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got ["Red &","Orange+","Green"]
  *  test case 2 failed: expected ['Red &', 'Orange+', 'Green', 'Orange', 'White'], got ["Red &"]
  */

char **remove_words(char **words, int word_count, const char *filter, int *new_count) {
    if (words == NULL || filter == NULL || new_count == NULL || word_count <= 0) {
        if (new_count != NULL) {
            *new_count = 0;
        }
        return NULL;
    }

    char **result = (char **)malloc(word_count * sizeof(char *));
    if (result == NULL) {
        *new_count = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < word_count; i++) {
        if (words[i] != NULL && strstr(words[i], filter) == NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(words[i]);
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
            memcpy(result[count], words[i], len + 1);
            count++;
        }
    }

    if (count == 0) {
        free(result);
        *new_count = 0;
        return NULL;
    }

    char **final_result = (char **)realloc(result, count * sizeof(char *));
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
        "Red color",
        "Orange#",
        "Green",
        "Orange @",
        "White"
    };
    int word_count = sizeof(words) / sizeof(words[0]);
    /* Possible weaknesses found:
     *  Variable 'new_count' is assigned a value that is never used. [unreadVariable]
     */
    int new_count = 0;

    char *filters[] = { "#", "&", "+", "@" };
    int filter_count = sizeof(filters) / sizeof(filters[0]);

    for (int f = 0; f < filter_count; f++) {
        new_count = 0;
        char **filtered = remove_words(words, word_count, filters[f], &new_count);

        printf("Filter '%s':\n", filters[f]);
        if (filtered != NULL) {
            for (int i = 0; i < new_count; i++) {
                printf("  '%s'\n", filtered[i]);
            }
            free_words(filtered, new_count);
        } else {
            printf("  No words remained\n");
        }
        printf("\n");
    }

    return 0;
}