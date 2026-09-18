#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_duplicate_words(char **words, int *count) {
    if (words == NULL || count == NULL || *count <= 0) {
        return;
    }

    int unique_count = 0;

    for (int i = 0; i < *count; i++) {
        if (words[i] == NULL) {
            continue;
        }

        int is_duplicate = 0;
        for (int j = 0; j < unique_count; j++) {
            if (words[j] != NULL && strcmp(words[i], words[j]) == 0) {
                is_duplicate = 1;
                break;
            }
        }

        if (is_duplicate) {
            free(words[i]);
            words[i] = NULL;
        } else {
            if (i != unique_count) {
                words[unique_count] = words[i];
                words[i] = NULL;
            }
            unique_count++;
        }
    }

    *count = unique_count;
}

int main(void) {
    int count = 6;
    char **words = (char **)malloc(count * sizeof(char *));
    
    if (words == NULL) {
        return 1;
    }

    words[0] = strdup("apple");
    words[1] = strdup("banana");
    words[2] = strdup("apple");
    words[3] = strdup("orange");
    words[4] = strdup("banana");
    words[5] = strdup("grape");

    for (int i = 0; i < count; i++) {
        if (words[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(words[j]);
            }
            free(words);
            return 1;
        }
    }

    remove_duplicate_words(words, &count);

    for (int i = 0; i < count; i++) {
        printf("%s\n", words[i]);
    }

    for (int i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);

    return 0;
}