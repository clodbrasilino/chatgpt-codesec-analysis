#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ADVERB_LENGTH 256

void findAdverbs(char sentence[]) {
    regex_t regex;
    regmatch_t match;
    const char* pattern = "\\b(\\w+ly)\\b";

    char *adverb = malloc((MAX_ADVERB_LENGTH + 1) * sizeof(char));
    if(adverb == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        printf("Regex compilation failed\n");
        free(adverb);
        return;
    }

    int offset = 0;
    while (regexec(&regex, sentence + offset, 1, &match, 0) == 0) {
        int position = offset + match.rm_so;
        int length = match.rm_eo - match.rm_so;
        length = (length >= MAX_ADVERB_LENGTH) ? MAX_ADVERB_LENGTH - 1 : length;

        /* Possible weaknesses found:
         *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
         */
        memcpy(adverb, sentence + position, length);
        adverb[length] = '\0';
        printf("Adverb: %s, Position: %d\n", adverb, position);
        offset += match.rm_eo;
    }

    regfree(&regex);
    free(adverb);
}

int main() {
    char sentence[] = "She quickly ran to the store.";

    findAdverbs(sentence);

    return 0;
}