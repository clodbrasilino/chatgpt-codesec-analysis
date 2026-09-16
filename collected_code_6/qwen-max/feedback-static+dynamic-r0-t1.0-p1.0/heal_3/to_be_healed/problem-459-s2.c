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
    char msgbuf[100];
    
    if (regcomp(&regex, "[A-Z]+", REG_EXTENDED|REG_NOSUB) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
    
    size_t len = strlen(str);
    char *new_str = (char *)malloc(len + 1);
    if (new_str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    int matched = 0;
    while (1) {
        regoff_t ovector[6];
        /* Possible weaknesses found:
         *  passing argument 4 of 'regexec' from incompatible pointer type [-Wincompatible-pointer-types]
         */
        reti = regexec(&regex, str, 3, ovector, 0);
        if (reti == 0) {
            size_t match_start = ovector[0];
            size_t match_end = ovector[1];
            memmove(str + match_start, str + match_end, len - match_end + 1);
            len -= (match_end - match_start);
            matched = 1;
        } else if (reti == REG_NOMATCH) {
            break;
        } else {
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            exit(1);
        }
    }

    if (matched) {
        strcpy(new_str, str);
        strcpy(str, new_str);
    }

    free(new_str);
    regfree(&regex);
}

int main() {
    char str[] = "aBcDeFgHiJkLmNoP";
    remove_uppercase_substrings(str);
    printf("%s\n", str);
    return 0;
}