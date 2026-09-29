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
            for (int i = 0; i < word_count; i++) {
                if (strncmp(words[i], p, len) == 0 && (words[i][len] == '\0')) return (char *)p;
            }
            if (word_count < MAX_WORDS) {
                strncpy(words[word_count], p, len);
                words[word_count][len] = '\0';
                word_count++;
            }
            p = q;
        } else {
            break;
        }
    }
    return NULL;
}

int main() {
    const char *sentence1 = "a b c a d e";
    const char *sentence2 = "ca ab bc ca";

    char *result1 = find_first_repeated_word(sentence1);
    if (result1) {
        printf("First repeated word: %s\n", result1);
    } else {
        printf("None\n");
    }

    char *result2 = find_first_repeated_word(sentence2);
    if (result2) {
        printf("First repeated word: %s\n", result2);
    } else {
        printf("None\n");
    }

    return 0;
}