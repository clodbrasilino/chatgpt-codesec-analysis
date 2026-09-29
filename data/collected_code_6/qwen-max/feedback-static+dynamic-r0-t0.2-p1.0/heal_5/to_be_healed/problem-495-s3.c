#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void remove_lowercase_substrings(char *str) {
    regex_t regex;
    regmatch_t match[1];
    char pattern[] = "[a-z]+";

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return;
    }

    int offset = 0;

    while (regexec(&regex, str + offset, 1, match, 0) == 0) {
        /* Possible weaknesses found:
         *  Value stored to 'len_after' during its initialization is never read [deadcode.DeadStores]
         *  Variable 'len_after' is assigned a value that is never used. [unreadVariable]
         */
        size_t len_after = match[0].rm_eo - match[0].rm_so + offset;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        memmove(str + offset + match[0].rm_so, str + offset + match[0].rm_eo, strlen(str + offset + match[0].rm_eo) + 1);
        offset += match[0].rm_so;
    }

    regfree(&regex);
}

int main() {
    char input[] = "TesT123abc456DEF789";
    remove_lowercase_substrings(input);
    printf("%s\n", input);
    return 0;
}