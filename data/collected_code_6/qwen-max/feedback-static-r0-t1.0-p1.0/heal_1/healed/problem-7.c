#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void findLongWords(const char *input, regex_t *compiled_regex) {
    regmatch_t matches[1];
    
    while (regexec(compiled_regex, input, 1, matches, 0) == 0) {
        if (matches[0].rm_so != -1 && matches[0].rm_eo != -1) {
            for (int j = matches[0].rm_so; j < matches[0].rm_eo; j++) {
                putchar(input[j]);
            }
            putchar('\n');
        }
        input += matches[0].rm_eo;
    }
}

int main() {
    const char *str = "This is a sample string with several words longer than three characters";
    regex_t compiled_regex;

    if (regcomp(&compiled_regex, "\\b\\w{4,}\\b", REG_EXTENDED | REG_NEWLINE) != 0) {
        return EXIT_FAILURE;
    }

    findLongWords(str, &compiled_regex);

    regfree(&compiled_regex);
    return EXIT_SUCCESS;
}