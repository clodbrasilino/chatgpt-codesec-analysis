#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void remove_lowercase_substrings(char *str) {
    if (str == NULL) {
        return;
    }

    regex_t regex;
    int reti;
    regmatch_t matches[1];

    reti = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (reti) {
        return;
    }

    char *current_pos = str;
    
    while (regexec(&regex, current_pos, 1, matches, 0) == 0) {
        size_t remaining_len = strlen(current_pos + matches[0].rm_eo);
        memmove(current_pos + matches[0].rm_so, current_pos + matches[0].rm_eo, remaining_len + 1);
    }

    regfree(&regex);
}

int main(void) {
    char test_str1[] = "Hello123world456TEST";
    char test_str2[] = "lowercaseONLY";
    char test_str3[] = "UPPERCASEONLY";
    char test_str4[] = "MixedCASEstring123";

    remove_lowercase_substrings(test_str1);
    printf("%s\n", test_str1);

    remove_lowercase_substrings(test_str2);
    printf("%s\n", test_str2);

    remove_lowercase_substrings(test_str3);
    printf("%s\n", test_str3);

    remove_lowercase_substrings(test_str4);
    printf("%s\n", test_str4);

    return 0;
}