#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_WORDS 100
#define WORD_LEN 256

char* find_first_repeated_word(const char *str) {
    char **words = (char **)malloc(MAX_WORDS * sizeof(char *));
    for (int i = 0; i < MAX_WORDS; i++) {
        words[i] = (char *)malloc(WORD_LEN);
    }
    int word_count = 0;

    while (*str) {
        const char *p = str;
        while (*p && (*p == ' ' || *p == '\t' || *p == '\n' || *p == ',')) p++;
        if (*p) {
            const char *q = p;
            while (*q && *q != ' ' && *q != '\t' && *q != '\n' && *q != ',') q++;
            size_t len = q - p;
            if (len >= WORD_LEN - 1) {
                str = q;
                continue;
            }
            for (int i = 0; i < word_count; i++) {
                if (strncmp(words[i], p, len) == 0 && (words[i][len] == '\0')) return (char *)p;
            }
            if (word_count < MAX_WORDS) {
                strncpy(words[word_count], p, len);
                words[word_count][len] = '\0';
                word_count++;
            }
            str = q;
        } else {
            break;
        }
    }

    for (int i = 0; i < MAX_WORDS; i++) {
        free(words[i]);
    }
    free(words);
    return NULL;
}

int main() {
    const char *sentence[] = {"a b a c", "hello world", "c a b c"};
    for (int i = 0; i < 3; i++) {
        const char *result = find_first_repeated_word(sentence[i]);
        if (result) {
            size_t len = strcspn(result, " \t\n,");
            printf("First repeated word: %.*s\n", (int)len, result);
        } else {
            printf("None\n");
        }
    }
    return 0;
}