#include <stdio.h>
#include <regex.h>
#include <string.h>

void find_sequences(const char *input) {
    regex_t regex;
    int reti;
    char msgbuf[100];

    if (regcomp(&regex, "[A-Z][a-z]+", REG_EXTENDED|REG_NEWLINE) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    regmatch_t pmatch[1];
    const size_t nmatch = 1;

    for (const char *ptr = input; ptr != NULL; ptr += pmatch[0].rm_eo) {
        reti = regexec(&regex, ptr, nmatch, pmatch, 0);
        if (reti == 0) {
            for (size_t i = 0; i < nmatch; i++) {
                if (pmatch[i].rm_so == -1)
                    break;
                printf("%.*s\n", (int)(pmatch[i].rm_eo - pmatch[i].rm_so), ptr + pmatch[i].rm_so);
            }
        } else if (reti == REG_NOMATCH) {
            break;
        } else {
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            break;
        }
    }

    regfree(&regex);
}

int main() {
    const char *input = "Hello World This Is A Test";
    find_sequences(input);
    return 0;
}