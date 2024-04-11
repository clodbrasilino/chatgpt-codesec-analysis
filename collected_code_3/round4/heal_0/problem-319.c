#include <stdio.h>
#include <string.h>
#include <regex.h>

void find_five_char_words(char *str) {
    regex_t regex;
    regmatch_t matches[2];
    char pattern[] = "\\b\\w{5}\\b";

    regcomp(&regex, pattern, REG_EXTENDED);

    while (regexec(&regex, str, 2, matches, 0) == 0) {
        int start = matches[0].rm_so;
        int end = matches[0].rm_eo;
        printf("%.*s\n", (end - start), (str + start));
        str += end;
    }

    regfree(&regex);
}

int main() {
    char str[] = "Hello world, this is a test string with several five words.";
    find_five_char_words(str);
    return 0;
}