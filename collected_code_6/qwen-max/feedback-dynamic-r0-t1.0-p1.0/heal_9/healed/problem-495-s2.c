#include <stdio.h>
#include <string.h>
#include <regex.h>

int remove_lowercase_substrings(char *str) {
    regex_t regex;
    regmatch_t match[1];
    int status, offset = 0;

    if (regcomp(&regex, "[a-z]+", REG_EXTENDED | REG_NOSUB) != 0) {
        return -1;
    }

    while (1) {
        status = regexec(&regex, str + offset, 1, match, 0);
        if (status == REG_NOMATCH)
            break;

        size_t len1 = match[0].rm_eo - (str + offset);
        size_t len2 = strlen(str + offset + match[0].rm_eo);
        memmove(str + offset + len1, str + offset + match[0].rm_eo, len2 + 1);
        offset += len1;
    }

    regfree(&regex);
    return 0;
}

int main() {
    char str[] = "TesTIngStrinG";
    remove_lowercase_substrings(str);
    printf("%s\n", str);
    return 0;
}