#include <stdio.h>
#include <regex.h>

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
        char adverb[match.rm_eo - match.rm_so + 1];
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