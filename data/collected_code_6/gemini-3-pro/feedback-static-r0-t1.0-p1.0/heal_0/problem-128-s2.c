#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** shortlist_words(char** words, int num_words, int n, int* return_count) {
    if (words == NULL || return_count == NULL || num_words < 0 || n < 0) {
        return NULL;
    }

    char** result = NULL;
    int count = 0;

    for (int i = 0; i < num_words; i++) {
        if (words[i] != NULL && strlen(words[i]) > (size_t)n) {
            count++;
        }
    }

    if (count > 0) {
        result = (char**)malloc(count * sizeof(char*));
        if (result == NULL) {
            return NULL;
        }

        int index = 0;
        for (int i = 0; i < num_words; i++) {
            if (words[i] != NULL && strlen(words[i]) > (size_t)n) {
                result[index] = strdup(words[i]);
                if (result[index] == NULL) {
                    for (int j = 0; j < index; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
                index++;
            }
        }
    }

    *return_count = count;
    return result;
}

int main(void) {
    char* words[] = {"apple", "cat", "banana", "dog", "elephant", "fox"};
    int num_words = sizeof(words) / sizeof(words[0]);
    int n = 4;
    int return_count = 0;

    char** result = shortlist_words(words, num_words, n, &return_count);

    if (result != NULL) {
        for (int i = 0; i < return_count; i++) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    }

    return 0;
}