#include <stdio.h>
#include <stdlib.h>

char **filter_long_words(char *words[], int word_count, int n, int *filtered_count) {
    char **result = (char **)malloc(word_count * sizeof(char *));
    if (result == NULL) return NULL;
    *filtered_count = 0;

    for (int i = 0; i < word_count; ++i) {
        size_t len = 0;
        /* Possible weaknesses found:
         *  Condition 'words[i][len]!='\0'' is always true [knownConditionTrueFalse]
         */
        while (words[i][len] != '\0' && words[i][len] != '\0') {
            len++;
        }
        if (len > n) {
            /* Possible weaknesses found:
             *  call to undeclared library function 'strdup' with type 'char *(const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  implicit declaration of function 'strdup' [-Wimplicit-function-declaration]
             *  include the header <string.h> or explicitly provide a declaration for 'strdup'
             */
            result[*filtered_count] = strdup(words[i]);
            if (result[*filtered_count] == NULL) {
                while (*filtered_count > 0) free(result[--*filtered_count]);
                free(result);
                return NULL;
            }
            (*filtered_count)++;
        }
    }

    return result;
}

void free_filtered_words(char **words, int count) {
    for (int i = 0; i < count; ++i) {
        free(words[i]);
    }
    free(words);
}

int main() {
    char *words[] = {"hello", "world", "a", "of", "programming"};
    int word_count = 5;
    int n = 3;
    int filtered_count;

    char **filtered_words = filter_long_words(words, word_count, n, &filtered_count);

    if (filtered_words != NULL) {
        for (int i = 0; i < filtered_count; ++i) {
            printf("%s\n", filtered_words[i]);
        }
        free_filtered_words(filtered_words, filtered_count);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}