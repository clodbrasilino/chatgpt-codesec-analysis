#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_five_char_words(const char *input_string) {
    if (input_string == NULL) {
        return;
    }

    regex_t regex;
    int reti;
    regmatch_t matches[1];
    const char *pattern = "\\b[a-zA-Z]{5}\\b";

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        return;
    }

    const char *cursor = input_string;
    while (1) {
        reti = regexec(&regex, cursor, 1, matches, 0);
        if (reti == 0) {
            int length = matches[0].rm_eo - matches[0].rm_so;
            if (length == 5) {
                printf("%.*s\n", length, cursor + matches[0].rm_so);
            }
            cursor += matches[0].rm_eo;
        } else if (reti == REG_NOMATCH) {
            break;
        } else {
            break;
        }
    }

    regfree(&regex);
}

int main(void) {
    const char *text = "This is a quick test string with some five letter words like apple and grape.";
    find_five_char_words(text);
    return 0;
}