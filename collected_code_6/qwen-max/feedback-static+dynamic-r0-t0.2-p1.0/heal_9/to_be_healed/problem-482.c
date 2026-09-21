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
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char msgbuf[1024];
            size_t len;
            /* Possible weaknesses found:
             *  possible fix: dereference with '*'
             *  passing argument 4 of 'regerror' makes integer from pointer without a cast [-Wint-conversion]
             *  incompatible pointer to integer conversion passing 'size_t *' (aka 'unsigned long *') to parameter of type 'size_t' (aka 'unsigned long'); remove & [-Wint-conversion]
             */
            regerror(reti, &regex, NULL, &len);
            if (len < sizeof(msgbuf)) {
                regerror(reti, &regex, msgbuf, sizeof(msgbuf));
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