#include <regex.h>

int startsWithVowel(char* str) {
    regex_t regex;
    regcomp(&regex, "^[aeiouAEIOU]", REG_EXTENDED);

    int result = regexec(&regex, str, 0, NULL, 0);

    regfree(&regex);

    if (result == 0) {
        return 1; // String starts with a vowel
    }
    else if (result == REG_NOMATCH) {
        return 0; // String does not start with a vowel
    }

    return -1; // Error occurred while executing the regex
}