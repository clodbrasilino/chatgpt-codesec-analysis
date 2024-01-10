#include <stdio.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strncpy'
  */

void findAdverbs(char sentence[]) {
    regex_t regex;
    regmatch_t match;

    // Compile the regex pattern for adverbs
    const char* pattern = "\\b(\\w+ly)\\b";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        printf("Regex compilation failed\n");
        return;
    }

    int offset = 0;
    while (regexec(&regex, sentence + offset, 1, &match, 0) == 0) {
        // Get the position of the adverb in the sentence
        int position = offset + match.rm_so;

        // Get the adverb from the matched string
        /* Possible weaknesses found:
         *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
         */
        char adverb[match.rm_eo - match.rm_so + 1];
        /* Possible weaknesses found:
         *  implicit declaration of function 'strncpy' [-Wimplicit-function-declaration]
         *  incompatible implicit declaration of built-in function 'strncpy' [-Wbuiltin-declaration-mismatch]
         *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
         *  include '<string.h>' or provide a declaration of 'strncpy'
         *  Cannot determine that 'adverb[0]' is initialized [premium-bughuntingUninit]
         */
        strncpy(adverb, sentence + position, match.rm_eo - match.rm_so);
        adverb[match.rm_eo - match.rm_so] = '\0';

        printf("Adverb: %s, Position: %d\n", adverb, position);

        // Move the offset to the end of the matched string
        offset += match.rm_eo;
    }

    regfree(&regex);
}

int main() {
    char sentence[] = "She quickly ran to the store.";

    findAdverbs(sentence);

    return 0;
}