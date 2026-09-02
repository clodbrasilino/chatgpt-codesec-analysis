#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **shortlist_words(char **words, int word_count, size_t n, int *result_count) {
    /* Possible weaknesses found:
     *  Assuming that condition 'result_count==NULL' is not redundant
     */
    if (words == NULL || result_count == NULL || word_count <= 0) {
        /* Possible weaknesses found:
         *  Either the condition 'result_count==NULL' is redundant or there is possible null pointer dereference: result_count. [nullPointerRedundantCheck]
         *  Null pointer dereference
         */
        *result_count = 0;
        return NULL;
    }

    char **result = NULL;
    int count = 0;
    int capacity = 0;

    for (int i = 0; i < word_count; i++) {
        if (words[i] != NULL && strlen(words[i]) > n) {
            if (count >= capacity) {
                int new_capacity = capacity == 0 ? 4 : capacity * 2;
                char **temp = realloc(result, new_capacity * sizeof(char *));
                if (temp == NULL) {
                    free(result);
                    *result_count = 0;
                    return NULL;
                }
                result = temp;
                capacity = new_capacity;
            }
            result[count] = words[i];
            count++;
        }
    }

    *result_count = count;
    return result;
}

int main(void) {
    char *words[] = {"apple", "banana", "kiwi", "strawberry", "pear", "grapefruit"};
    int word_count = sizeof(words) / sizeof(words[0]);
    int result_count = 0;

    char **long_words = shortlist_words(words, word_count, 5, &result_count);

    if (long_words != NULL) {
        for (int i = 0; i < result_count; i++) {
            printf("%s\n", long_words[i]);
        }
        free(long_words);
    }

    return 0;
}