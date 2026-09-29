#include <stdio.h>
#include <regex.h>
#include <string.h>

void find_sequences(const char *input) {
    regex_t regex;
    if (regcomp(&regex, "[A-Z][a-z]+", REG_EXTENDED|REG_NEWLINE) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    regmatch_t pmatch[1];
    const size_t nmatch = 1;

    for (const char *ptr = input; *ptr != '\0'; ptr++) {
        int reti = regexec(&regex, ptr, nmatch, pmatch, 0);
        if (!reti) {
            for (int i = 0; i < nmatch; i++) {
                if (pmatch[i].rm_so == -1)
                    break;
                printf("%.*s\n", (int)(pmatch[i].rm_eo - pmatch[i].rm_so), ptr + pmatch[i].rm_so);
            }
            ptr += pmatch[0].rm_eo - 1;
        } else if (reti == REG_NOMATCH) {
            continue;
        } else {
            char msgbuf[1024];
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            size_t len;
            regerror(reti, &regex, NULL, (size_t *)&len);
            if (len < sizeof(msgbuf)) {
                fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            } else {
                fprintf(stderr, "Regex match failed, but error message was too long to display.\n");
            }
            break;
        }
    }

    regfree(&regex);
}

int main() {
    const char *test_string = "Hello World ATest BTest cTest DTest";
    find_sequences(test_string);
    return 0;
}