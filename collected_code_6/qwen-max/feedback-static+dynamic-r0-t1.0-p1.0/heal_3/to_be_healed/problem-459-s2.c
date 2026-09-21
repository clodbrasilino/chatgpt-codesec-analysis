#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void remove_uppercase_substrings(char *str) {
    regex_t regex;
    /* Possible weaknesses found:
     *  The scope of the variable 'reti' can be reduced. [variableScope]
     */
    int reti;

    if (regcomp(&regex, "[A-Z]+", REG_EXTENDED|REG_NOSUB) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    while (1) {
        reti = regexec(&regex, str, 0, NULL, 0);
        if (reti == 0) {
            regoff_t ovector[6];
            /* Possible weaknesses found:
             *  passing argument 4 of 'regexec' from incompatible pointer type [-Wincompatible-pointer-types]
             */
            reti = regexec(&regex, str, 3, ovector, 0);
            if (reti == 0) {
                size_t match_start = ovector[0];
                size_t match_end = ovector[1];
                /* Possible weaknesses found:
                 * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                 */
                memmove(str + match_start, str + match_end, strlen(str + match_end) + 1 - (match_end - match_start));
            } else {
                break;
            }
        } else if (reti == REG_NOMATCH) {
            break;
        } else {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char msgbuf[100];
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            exit(1);
        }
    }

    regfree(&regex);
}

int main() {
    char str[] = "aBcDeFgHiJkLmNoP";
    remove_uppercase_substrings(str);
    printf("%s\n", str);
    return 0;
}