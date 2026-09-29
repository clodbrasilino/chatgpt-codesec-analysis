#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_adverbs(const char *sentence) {
    regex_t regex;
    regmatch_t match[1];
    const char *pattern = "\\b[a-zA-Z]+ly\\b";
    int ret;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        char error_message[100];
        regerror(ret, &regex, error_message, sizeof(error_message));
        fprintf(stderr, "Could not compile regex: %s\n", error_message);
        return;
    }

    const char *cursor = sentence;
    while (1) {
        ret = regexec(&regex, cursor, 1, match, 0);
        if (ret == REG_NOMATCH) {
            break;
        } else if (ret != 0) {
            char error_message[100];
            regerror(ret, &regex, error_message, sizeof(error_message));
            fprintf(stderr, "Regex match failed: %s\n", error_message);
            regfree(&regex);
            return;
        }

        printf("Adverb: %.*s, Position: %ld\n", (int)(match[0].rm_eo - match[0].rm_so), cursor + match[0].rm_so, (long)(cursor - sentence + match[0].rm_so));
        cursor += match[0].rm_eo;
    }

    regfree(&regex);
}

int main() {
    const char *sentence = "She quickly ran to the store and carefully picked the items.";
    find_adverbs(sentence);
    return 0;
}