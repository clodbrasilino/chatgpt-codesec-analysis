#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got ["Red &","Orange+","Green"]
  *  test case 2 failed: expected ['Red &', 'Orange+', 'Green', 'Orange', 'White'], got ["Red &"]
  *  test case 0 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got ["Red color","Orange#","Green"]
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
        if (words[i] != NULL && (filter[0] == '\0' || strstr(words[i], filter) == NULL)) {
            result[count] = (char *)malloc((strlen(words[i]) + 1) * sizeof(char));
            if (result[count] == NULL) {
                for (int j = 0; j < count; j++) {
                    free(result[j]);
                }
                free(result);
                *new_count = 0;
                return NULL;
            }
            strcpy(result[count], words[i]);
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
        for (int i = 0; i < count; i++) {
            free(result[i]);
        }
        free(result);
        *new_count = 0;
        return NULL;
    }

    *new_count = count;
    return final_result;
}

int main(void) {
    char *words[] = {"Red", "", "Green", "Orange", "White"};
    int word_count = sizeof(words) / sizeof(words[0]);
    int new_count = 0;

    char **filtered = remove_words(words, word_count, "a", &new_count);

    if (filtered != NULL) {
        for (int i = 0; i < new_count; i++) {
            printf("%s\n", filtered[i]);
            free(filtered[i]);
        }
        free(filtered);
    } else {
        printf("No words remain after filtering.\n");
    }

    return 0;
}