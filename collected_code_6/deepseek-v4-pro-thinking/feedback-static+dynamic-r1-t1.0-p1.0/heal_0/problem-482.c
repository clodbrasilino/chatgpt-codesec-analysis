#include <stdio.h>
#include <regex.h>

void find_sequences(const char *str) {
    regex_t regex;
    regmatch_t match;
    int reti;
    const char *p = str;

    reti = regcomp(&regex, "[A-Z][a-z]+", REG_EXTENDED);
    if (reti != 0) {
        char errbuf[256];
        regerror(reti, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "regcomp: %s\n", errbuf);
        return;
    }

    while (*p != '\0') {
        reti = regexec(&regex, p, 1, &match, 0);
        if (reti == REG_NOMATCH) {
            break;
        } else if (reti != 0) {
            char errbuf[256];
            regerror(reti, &regex, errbuf, sizeof(errbuf));
            fprintf(stderr, "regexec: %s\n", errbuf);
            break;
        }

        printf("%.*s\n", (int)(match.rm_eo - match.rm_so), p + match.rm_so);
        p += match.rm_eo;
    }

    regfree(&regex);
}

int main(void) {
    const char *text = "Hello World foo Bar BazTest";
    find_sequences(text);
    return 0;
}