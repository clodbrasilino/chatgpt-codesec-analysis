#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_sequences(const char *text) {
    if (text == NULL) {
        return;
    }

    regex_t regex;
    int reti;
    regmatch_t pmatch[1];
    const char *pattern = "[a-z]+_[a-z]+";
    const char *p = text;

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    while (regexec(&regex, p, 1, pmatch, 0) == 0) {
        int start = pmatch[0].rm_so;
        int end = pmatch[0].rm_eo;
        int len = end - start;

        if (len > 0) {
            char *match = malloc(len + 1);
            if (match == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                regfree(&regex);
                return;
            }

            snprintf(match, len + 1, "%.*s", len, p + start);
            printf("%s\n", match);

            free(match);
        }
        p += end;
    }

    regfree(&regex);
}

int main(void) {
    const char *test_string = "hello_world is a test_string with multiple_matches and Some_Invalid ones like TEST_str";
    find_sequences(test_string);
    return 0;
}