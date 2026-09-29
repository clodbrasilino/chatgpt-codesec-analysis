#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

void find_sequences(const char *input) {
    regex_t regex;
    if (regcomp(&regex, "[A-Z][a-z]+", REG_EXTENDED | REG_NEWLINE)) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    regmatch_t pmatch[1];
    const size_t nmatch = 1;

    for (const char *ptr = input; *ptr;) {
        int reti = regexec(&regex, ptr, nmatch, pmatch, 0);
        if (reti == 0) {
            for (size_t i = 0; i < nmatch; i++) {
                if (pmatch[i].rm_so == -1)
                    break;
                printf("%.*s\n", (int)(pmatch[i].rm_eo - pmatch[i].rm_so), ptr + pmatch[i].rm_so);
            }
            ptr += pmatch[0].rm_eo;
        } else if (reti == REG_NOMATCH) {
            break;
        } else {
            char *msgbuf = (char *)malloc(100);
            if (msgbuf == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                regfree(&regex);
                exit(EXIT_FAILURE);
            }
            regerror(reti, &regex, msgbuf, 100);
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            if (strlen(msgbuf) < 99) {
                fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            } else {
                fprintf(stderr, "Regex match failed: Error message too long\n");
            }
            free(msgbuf);
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