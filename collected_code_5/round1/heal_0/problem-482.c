#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

void find_sequences(char *str) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "[A-Z][a-z]*", 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    regmatch_t matches[1]; 

    while (1) {
        reti = regexec(&regex, str, 1, matches, 0);
        if (!reti) {
            printf ("Found match: %.*s\n", (int)(matches[0].rm_eo - matches[0].rm_so), 
                                               str + matches[0].rm_so);
            str += matches[0].rm_eo;
        } else if (reti == REG_NOMATCH) {
            break;
        } else {
            char msgbuf[100];
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            exit(1);
        }
    }

    regfree(&regex);
}

int main() {
    char str[] = "HelloWorld ThisIsA Test";
    find_sequences(str);
    return 0;
}