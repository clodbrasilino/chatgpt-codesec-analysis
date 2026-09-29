#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void find_sequences(const char *text) {
    regex_t regex;
    regmatch_t match[1];
    int reti;
    const char *pattern = "[a-z]+_[a-z]+";

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    const char *cursor = text;
    while ((reti = regexec(&regex, cursor, 1, match, 0)) == 0) {
        int length = match[0].rm_eo - match[0].rm_so;
        char *matched = (char *)malloc((size_t)(length + 1));
        if (matched == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            regfree(&regex);
            return;
        }

        strncpy(matched, cursor + match[0].rm_so, (size_t)length);
        matched[length] = '\0';

        printf("Found: %s\n", matched);
        free(matched);

        cursor += match[0].rm_eo;
    }

    if (reti != REG_NOMATCH) {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    }

    regfree(&regex);
}

int main(void) {
    const char *test_string = "hello_world is a test_sequence but THIS_IS_NOT and this_is valid.";
    find_sequences(test_string);
    return 0;
}