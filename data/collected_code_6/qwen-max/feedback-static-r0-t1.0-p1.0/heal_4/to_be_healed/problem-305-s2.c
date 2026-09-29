#include <stdio.h>
#include <string.h>

int match_words(const char *word1, const char *word2) {
    return strcmp(word1, word2) == 0;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const char *words[5] = {"python", "programming", "project", "practice", "passion"};
    int found = 0;

    for (int i = 0; i < 5; i++) {
        if (words[i][0] == 'p') {
            for (int j = i + 1; j < 5; j++) {
                if (words[j][0] == 'p' && match_words(words[i], words[j])) {
                    printf("Matched: %s and %s\n", words[i], words[j]);
                    found = 1;
                }
            }
        }
    }

    if (!found) {
        printf("No matches found.\n");
    }

    return 0;
}