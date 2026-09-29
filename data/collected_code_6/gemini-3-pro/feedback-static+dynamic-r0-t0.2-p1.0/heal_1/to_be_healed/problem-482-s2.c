#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_sequences(const char *str) {
    if (str == NULL) {
        return;
    }

    regex_t regex;
    int reti;
    regmatch_t pmatch[1];
    const char *p = str;

    reti = regcomp(&regex, "[A-Z][a-z]+", REG_EXTENDED);
    if (reti) {
        return;
    }

    while (regexec(&regex, p, 1, pmatch, 0) == 0) {
        int start = pmatch[0].rm_so;
        int end = pmatch[0].rm_eo;
        int len = end - start;

        char *match = (char *)malloc(len + 1);
        if (match != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(match, p + start, len);
            match[len] = '\0';
            printf("%s\n", match);
            free(match);
        }

        p += end;
    }

    regfree(&regex);
}

int main(void) {
    const char *test_str = "Hello world, this is a Test String with Some Sequences.";
    find_sequences(test_str);
    return 0;
}