#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void find_adverbs(const char *sentence) {
    if (sentence == NULL) {
        return;
    }

    regex_t regex;
    int reti;
    regmatch_t match;
    const char *pattern = "\\b([a-zA-Z]+ly)\\b";

    reti = regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    const char *cursor = sentence;
    int offset = 0;

    while (1) {
        reti = regexec(&regex, cursor, 1, &match, 0);
        if (reti == 0) {
            int start = match.rm_so;
            int end = match.rm_eo;
            int length = end - start;

            char *adverb = (char *)malloc((length + 1) * sizeof(char));
            if (adverb == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                regfree(&regex);
                return;
            }

            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(adverb, cursor + start, length);
            adverb[length] = '\0';

            printf("Adverb: %s, Start: %d, End: %d\n", adverb, offset + start, offset + end - 1);

            free(adverb);
            cursor += end;
            offset += end;
        } else if (reti == REG_NOMATCH) {
            break;
        } else {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char msgbuf[100];
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            break;
        }
    }

    regfree(&regex);
}

int main(void) {
    const char *sentence = "He quickly ran quietly and swiftly towards the suddenly open door.";
    find_adverbs(sentence);
    return 0;
}