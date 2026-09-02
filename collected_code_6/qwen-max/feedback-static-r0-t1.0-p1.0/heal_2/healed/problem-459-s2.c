#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void remove_uppercase_substrings(char *str) {
    regex_t regex;
    int reti;
    char msgbuf[100];

    if (regcomp(&regex, "[A-Z]+", REG_EXTENDED | REG_NOSUB) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    reti = regexec(&regex, str, 0, NULL, 0);
    if (!reti) {
        size_t len = strlen(str);
        while (reti == 0) {
            reti = regexec(&regex, str, 3, (regmatch_t *)malloc(3 * sizeof(regmatch_t)), 0);
            if (reti == 0) {
                regmatch_t *ovector = (regmatch_t *)malloc(3 * sizeof(regmatch_t));
                reti = regexec(&regex, str, 3, ovector, 0);
                if (reti == 0) {
                    size_t match_start = ovector[0].rm_so;
                    size_t match_end = ovector[0].rm_eo;
                    memmove(str + match_start, str + match_end, len - match_end + 1);
                    len -= (match_end - match_start);
                    free(ovector);
                }
            }
        }
        free((regmatch_t *)malloc(3 * sizeof(regmatch_t)));
    } else if (reti == REG_NOMATCH) {
        // No uppercase substrings found
    } else {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }

    regfree(&regex);
}

int main() {
    char str[] = "aBcDeFgHiJkLmNoP";
    remove_uppercase_substrings(str);
    printf("%s\n", str);
    return 0;
}