#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contains_any_filter(const char *word, const char *filter) {
    if (word == NULL || filter == NULL) {
        return 0;
    }
    
    for (int i = 0; filter[i] != '\0'; i++) {
        if (strchr(word, filter[i]) != NULL) {
            return 1;
        }
    }
    return 0;
}

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
    char *words[] = {"Red &", "Orange+", "Green", "Orange", "White"};
    int word_count = sizeof(words) / sizeof(words[0]);
    int new_count = 0;
    const char filter[] = "&#";

    char **filtered = remove_words(words, word_count, filter, &new_count);

    if (filtered != NULL) {
        for (int i = 0; i < new_count; i++) {
            printf("%s\n", filtered[i]);
            free(filtered[i]);
        }
        free(filtered);
    } else {
        printf("No words remaining or error occurred.\n");
    }

    return 0;
}