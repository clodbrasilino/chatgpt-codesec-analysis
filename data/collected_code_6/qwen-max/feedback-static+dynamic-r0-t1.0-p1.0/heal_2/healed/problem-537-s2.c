#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORDS 100
#define WORD_LEN 256

char* find_first_repeated_word(const char *str) {
    char words[MAX_WORDS][WORD_LEN] = {""};
    int word_count = 0;
    const char *p = str, *q;

    while (*p) {
        while (*p && (*p == ' ' || *p == '\t' || *p == '\n' || *p == ',')) p++;
        if (*p) {
            q = p;
            while (*q && *q != ' ' && *q != '\t' && *q != '\n' && *q != ',') q++;
            int len = q - p;
            if (len >= WORD_LEN) continue;
            for (int i = 0; i < word_count; i++) {
                if (strncmp(words[i], p, len) == 0 && (words[i][len] == '\0')) return (char *)p;
            }
            if (word_count < MAX_WORDS) {
                strncpy(words[word_count], p, len);
                words[word_count][len] = '\0';
                word_count++;
            }
            p = q;
        }
    }
    return NULL;
}

int main() {
    const char *sentence[] = {"a b a c", "hello world", "c a b c"};
    for (int i = 0; i < 3; i++) {
        char *result = find_first_repeated_word(sentence[i]);
        if (result) {
            printf("First repeated word: %.*s\n", (int)strlen(result), result);
        } else {
            printf("None\n");
        }
    }
    return 0;
}