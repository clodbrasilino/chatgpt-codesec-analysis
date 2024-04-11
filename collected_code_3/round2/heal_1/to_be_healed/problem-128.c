#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **shortlist_words(char **words, int word_count, int n, int *shortlisted_count) {
    char **shortlisted_words = (char **)malloc(sizeof(char *) * word_count);
    *shortlisted_count = 0;

    for (int i = 0; i < word_count; i++) {
        if (strlen(words[i]) > n) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'shortlisted_words' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            shortlisted_words[*shortlisted_count] = words[i];
            (*shortlisted_count)++;
        }
    }

    return shortlisted_words;
}

int main() {
    char *words[] = {"Hello", "World", "Programming", "C", "Language"};
    int word_count = sizeof(words) / sizeof(words[0]);
    int shortlisted_count;
    int n = 5;

    char **shortlisted_words = shortlist_words(words, word_count, n, &shortlisted_count);

    for (int i = 0; i < shortlisted_count; i++) {
        printf("%s\n", shortlisted_words[i]);
    }

    free(shortlisted_words);

    return 0;
}