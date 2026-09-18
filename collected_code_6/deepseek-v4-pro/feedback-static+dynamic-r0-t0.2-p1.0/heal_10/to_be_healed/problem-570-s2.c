#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contains_any_filter(const char *word, const char *filter) {
    if (word == NULL || filter == NULL) {
        return 0;
    }
    
    if (*word == '\0') {
        return 0;
    }
    
    for (int i = 0; filter[i] != '\0'; i++) {
        if (strchr(word, filter[i]) != NULL) {
            return 1;
        }
    }
    return 0;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got ["Orange#","Green"]
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

    int *keep_flags = (int *)malloc(word_count * sizeof(int));
    if (keep_flags == NULL) {
        *new_count = 0;
        return NULL;
    }

    int kept = 0;
    for (int i = 0; i < word_count; i++) {
        if (words[i] != NULL && !contains_any_filter(words[i], filter)) {
            keep_flags[i] = 1;
            kept++;
        } else {
            keep_flags[i] = 0;
        }
    }

    if (kept == 0) {
        free(keep_flags);
        *new_count = 0;
        return NULL;
    }

    char **result = (char **)malloc(kept * sizeof(char *));
    if (result == NULL) {
        free(keep_flags);
        *new_count = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < word_count; i++) {
        if (keep_flags[i]) {
            result[index] = (char *)malloc(strlen(words[i]) + 1);
            if (result[index] == NULL) {
                for (int j = 0; j < index; j++) {
                    free(result[j]);
                }
                free(result);
                free(keep_flags);
                *new_count = 0;
                return NULL;
            }
            strcpy(result[index], words[i]);
            index++;
        }
    }

    free(keep_flags);
    *new_count = kept;
    return result;
}

int main(void) {
    char *words1[] = {"Red", "", "Green", "Orange", "White"};
    int word_count1 = sizeof(words1) / sizeof(words1[0]);
    int new_count1 = 0;
    const char filter1[] = "&#";

    char **filtered1 = remove_words(words1, word_count1, filter1, &new_count1);

    printf("Test case 0:\n");
    if (filtered1 != NULL) {
        printf("[");
        for (int i = 0; i < new_count1; i++) {
            printf("'%s'", filtered1[i]);
            if (i < new_count1 - 1) printf(", ");
            free(filtered1[i]);
        }
        printf("]\n");
        free(filtered1);
    } else {
        printf("[]\n");
    }

    char *words2[] = {"Red &", "Orange+", "Green", "Orange", "White"};
    int word_count2 = sizeof(words2) / sizeof(words2[0]);
    int new_count2 = 0;
    const char filter2[] = "&+";

    char **filtered2 = remove_words(words2, word_count2, filter2, &new_count2);

    printf("Test case 1:\n");
    if (filtered2 != NULL) {
        printf("[");
        for (int i = 0; i < new_count2; i++) {
            printf("'%s'", filtered2[i]);
            if (i < new_count2 - 1) printf(", ");
            free(filtered2[i]);
        }
        printf("]\n");
        free(filtered2);
    } else {
        printf("[]\n");
    }

    char *words3[] = {"Red &", "Orange+", "Green", "Orange", "White"};
    int word_count3 = sizeof(words3) / sizeof(words3[0]);
    int new_count3 = 0;
    const char filter3[] = "+";

    char **filtered3 = remove_words(words3, word_count3, filter3, &new_count3);

    printf("Test case 2:\n");
    if (filtered3 != NULL) {
        printf("[");
        for (int i = 0; i < new_count3; i++) {
            printf("'%s'", filtered3[i]);
            if (i < new_count3 - 1) printf(", ");
            free(filtered3[i]);
        }
        printf("]\n");
        free(filtered3);
    } else {
        printf("[]\n");
    }

    return 0;
}