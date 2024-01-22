#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ADVERB_LENGTH 256

void findAdverbs(char sentence[]) {
    regex_t regex;
    regmatch_t match;
    const char* pattern = "\\b(\\w+ly)\\b";

    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char adverb[MAX_ADVERB_LENGTH + 1];

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        printf("Regex compilation failed\n");
        return;
    }

    int offset = 0;
    while (regexec(&regex, sentence + offset, 1, &match, 0) == 0) {
        int position = offset + match.rm_so;
        int length = match.rm_eo - match.rm_so;
        length = (length >= MAX_ADVERB_LENGTH) ? MAX_ADVERB_LENGTH - 1 : length;
        
        /* Possible weaknesses found:
         *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
         */
        strncpy(adverb, sentence + position, length);
        adverb[length] = '\0';
        printf("Adverb: %s, Position: %d\n", adverb, position);
        offset += match.rm_eo;
    }

    regfree(&regex);
}

int main() {
    char sentence[] = "She quickly ran to the store.";

    findAdverbs(sentence);

    return 0;
}