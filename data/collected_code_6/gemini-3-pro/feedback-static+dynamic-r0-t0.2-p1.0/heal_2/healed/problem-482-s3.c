#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_sequences(const char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    const char *pattern = "[A-Z][a-z]+";
    int reti;
    const char *cursor = str;

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    while (1) {
        reti = regexec(&regex, cursor, 1, pmatch, 0);
        if (reti == 0) {
            int start = pmatch[0].rm_so;
            int end = pmatch[0].rm_eo;
            
            if (end <= start) {
                break;
            }
            
            int len = end - start;
            
            char *match = (char *)malloc(len + 1);
            if (match == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                regfree(&regex);
                return;
            }
            
            snprintf(match, len + 1, "%.*s", len, cursor + start);
            
            printf("%s\n", match);
            free(match);
            
            cursor += end;
        } else if (reti == REG_NOMATCH) {
            break;
        } else {
            size_t required_size = regerror(reti, &regex, NULL, 0);
            char *msgbuf = (char *)malloc(required_size);
            if (msgbuf != NULL) {
                regerror(reti, &regex, msgbuf, required_size);
                fprintf(stderr, "Regex match failed: %s\n", msgbuf);
                free(msgbuf);
            } else {
                fprintf(stderr, "Regex match failed\n");
            }
            break;
        }
    }

    regfree(&regex);
}

int main(void) {
    const char *test_string = "Hello world, This Is a Test String with Some Sequences.";
    find_sequences(test_string);
    return 0;
}