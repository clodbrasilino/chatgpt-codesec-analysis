#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **shortlist_words(char **words, int word_count, int n, int *result_count) {
    char **result = (char **)malloc(sizeof(char *) * word_count);
    if (result == NULL) {
        *result_count = 0;
        return NULL;
    }
    int count = 0;
    for(int i = 0; i < word_count; i++) {
        if(strlen(words[i]) > n) {
            result[count] = words[i];
            count++;
        }
    }
    *result_count = count;
    return result;
}

int main() {
    char *words[] = {"apple", "banana", "cherry", "date", "elderberry"};
    int word_count = sizeof(words) / sizeof(words[0]);
    int n = 5;
    int result_count;
    char **result = shortlist_words(words, word_count, n, &result_count);
    if(result == NULL){
        return 1;
    }
    for(int i = 0; i < result_count; i++) {
        printf("%s\n", result[i]);
    }
    free(result);
    return 0;
}