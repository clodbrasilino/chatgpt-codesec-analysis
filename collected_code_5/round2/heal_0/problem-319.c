#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void find_five_char_words(const char* str) {
    regex_t regex;
    regmatch_t matches[1];
    if (regcomp(&regex, "\\b\\w{5}\\b", REG_EXTENDED) != 0) {
        return;
    }
    while (str && *str) {
        if (regexec(&regex, str, 1, matches, 0) == 0) {
            char match[6] = {0};
            strncpy(match, str+matches[0].rm_so, matches[0].rm_eo-matches[0].rm_so);
            printf("%s\n", match);
            str += matches[0].rm_eo;
        } else {
            regfree(&regex);
            return;
        }
    }
    regfree(&regex);
}

int main() {
    const char* str = "Hello, World! Check this sample. Jade, Olive and Lodge.";
    find_five_char_words(str);
    return 0;
}