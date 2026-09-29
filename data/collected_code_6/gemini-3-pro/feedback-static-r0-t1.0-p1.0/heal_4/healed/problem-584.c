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

            if (length <= 0) {
                break;
            }

            printf("Adverb: %.*s, Start: %d, End: %d\n", length, cursor + start, offset + start, offset + end - 1);

            cursor += end;
            offset += end;
        } else if (reti == REG_NOMATCH) {
            break;
        } else {
            size_t req_size = regerror(reti, &regex, NULL, 0);
            char *msgbuf = (char *)malloc(req_size);
            if (msgbuf != NULL) {
                regerror(reti, &regex, msgbuf, req_size);
                fprintf(stderr, "Regex match failed: %s\n", msgbuf);
                free(msgbuf);
            } else {
                fprintf(stderr, "Regex match failed, and memory allocation for error message failed\n");
            }
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