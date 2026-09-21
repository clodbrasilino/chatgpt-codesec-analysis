#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int add_spaces_between_capital_words(char *str) {
    regex_t regex;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     *  Unused variable: buffer [unusedVariable]
     */
    char buffer[1024];
    regmatch_t pmatch[1];

    int reti = regcomp(&regex, "([A-Z])", REG_EXTENDED);
    if (reti != 0) {
        return -1;
    }

    while (regexec(&regex, str, 1, pmatch, 0) == 0) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(str + pmatch[0].rm_so) + 1;
        memmove(str + pmatch[0].rm_eo + 1, str + pmatch[0].rm_so, len);
        str[pmatch[0].rm_so] = ' ';
        str += pmatch[0].rm_eo + 1;
    }

    regfree(&regex);
    return 0;
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    if (add_spaces_between_capital_words(str) != -1) {
        printf("%s\n", str);
    } else {
        perror("Regex error");
        exit(EXIT_FAILURE);
    }
    return 0;
}