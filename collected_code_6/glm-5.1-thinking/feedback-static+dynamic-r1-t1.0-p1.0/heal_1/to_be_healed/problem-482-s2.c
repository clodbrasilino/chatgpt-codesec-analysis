#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_sequences(const char *str) {
    regex_t regex;
    regmatch_t matches[1];
    int reti;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char errbuf[100];

    reti = regcomp(&regex, "[A-Z][a-z]*", REG_EXTENDED);
    if (reti) {
        regerror(reti, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        regfree(&regex);
        return;
    }

    const char *p = str;
    while (1) {
        reti = regexec(&regex, p, 1, matches, 0);
        if (reti == REG_NOMATCH) {
            break;
        } else if (reti != 0) {
            regerror(reti, &regex, errbuf, sizeof(errbuf));
            fprintf(stderr, "Regex execution failed: %s\n", errbuf);
            break;
        }

        int start = matches[0].rm_so;
        int end = matches[0].rm_eo;
        printf("%.*s\n", end - start, p + start);

        p += end;
    }

    regfree(&regex);
}

int main(void) {
    find_sequences("Hello World THIS is A Test of Regex");
    return 0;
}