#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_sequences(const char *str) {
    if (str == NULL) {
        return;
    }

    regex_t regex;
    int ret;
    const char *pattern = "[A-Z][a-z]+";
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    regmatch_t pmatch[1];
    const char *p = str;

    while (1) {
        ret = regexec(&regex, p, 1, pmatch, 0);
        if (ret == 0) {
            int start = pmatch[0].rm_so;
            int end = pmatch[0].rm_eo;
            int len = end - start;
            
            char *match = malloc((len + 1) * sizeof(char));
            if (match == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                break;
            }
            
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(match, p + start, len);
            match[len] = '\0';
            printf("Found: %s\n", match);
            free(match);
            
            p += end;
        } else if (ret == REG_NOMATCH) {
            break;
        } else {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char msgbuf[100];
            regerror(ret, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            break;
        }
    }

    regfree(&regex);
}

int main(void) {
    const char *test_str = "This is a Test String with Some Sequences of Upper and lower Case Letters.";
    find_sequences(test_str);
    return 0;
}