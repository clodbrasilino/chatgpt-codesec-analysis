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

    int count = 0;
    int filter_len = strlen(filter);
    int *keep_flags = (int *)malloc(word_count * sizeof(int));
    
    if (keep_flags == NULL) {
        *new_count = 0;
        return NULL;
    }

    for (int i = 0; i < word_count; i++) {
        if (words[i] != NULL && (filter_len == 0 || strstr(words[i], filter) == NULL)) {
            keep_flags[count] = i;
            count++;
        }
    }

    if (count == 0) {
        free(keep_flags);
        *new_count = 0;
        return NULL;
    }

    char **result = (char **)malloc(count * sizeof(char *));
    if (result == NULL) {
        free(keep_flags);
        *new_count = 0;
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        int idx = keep_flags[i];
        result[i] = (char *)malloc((strlen(words[idx]) + 1) * sizeof(char));
        if (result[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            free(keep_flags);
            *new_count = 0;
            return NULL;
        }
        strcpy(result[i], words[idx]);
    }

    free(keep_flags);
    *new_count = count;
    return result;
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