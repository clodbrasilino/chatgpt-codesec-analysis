#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_sequences(const char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    const char *pattern = "[A-Z][a-z]+";
    int reti;
    const char *cursor = str;

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    while (1) {
        reti = regexec(&regex, cursor, 1, pmatch, 0);
        if (!reti) {
            int start = pmatch[0].rm_so;
            int end = pmatch[0].rm_eo;
            int len = end - start;
            
            char *match = (char *)malloc(len + 1);
            if (match == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                regfree(&regex);
                return;
            }
            
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(match, cursor + start, len);
            match[len] = '\0';
            
            printf("%s\n", match);
            free(match);
            
            cursor += end;
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
    const char *test_string = "Hello world, This Is a Test String with Some Sequences.";
    find_sequences(test_string);
    return 0;
}