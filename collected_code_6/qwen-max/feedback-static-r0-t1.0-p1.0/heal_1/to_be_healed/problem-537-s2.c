#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORDS 100
#define WORD_LEN 256

char* find_first_repeated_word(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
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
    const char *sentence = "the quick brown fox jumps over the lazy dog";
    char *result = find_first_repeated_word(sentence);
    if (result) {
        printf("First repeated word: %s\n", result);
    } else {
        printf("No repeated words found.\n");
    }
    return 0;
}