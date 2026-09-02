#include <stdio.h>
#include <regex.h>
#include <string.h>

void find_sequences(const char *input) {
    regex_t regex;
    /* Possible weaknesses found:
     *  The scope of the variable 'reti' can be reduced. [variableScope]
     */
    int reti;
    char msgbuf[100];

    if (regcomp(&regex, "[A-Z][a-z]+", REG_EXTENDED | REG_NEWLINE) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    regmatch_t pmatch[1];
    const size_t nmatch = 1;

    for (const char *ptr = input; ptr != NULL; ptr += pmatch[0].rm_eo) {
        reti = regexec(&regex, ptr, nmatch, pmatch, 0);
        if (reti == 0) {
            printf("Found: %.*s\n", pmatch[0].rm_eo - pmatch[0].rm_so, &ptr[pmatch[0].rm_so]);
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
    const char *test_string = "This is a Test String with SomeWords and OtherWords";
    find_sequences(test_string);
    return 0;
}