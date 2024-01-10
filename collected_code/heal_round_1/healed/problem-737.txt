#include <stddef.h>
#include <regex.h>

int startsWithVowel(const char* str) {
    regex_t regex;
    if (regcomp(&regex, "^[aeiouAEIOU]", REG_EXTENDED)) {
        return -1; // Compilation failed, error occurred
    }
  
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

int main() {
    const char* str1 = "Apple";
    const char* str2 = "Banana";

    int res1 = startsWithVowel(str1);
    int res2 = startsWithVowel(str2);

    return 0;
}