#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void remove_lowercase_substrings(char *str) {
    regex_t regex;
    char result[1024] = "";
    regmatch_t pmatch[1];
    int nmatch = 1;
    int pos = 0;

    if (regcomp(&regex, "[a-z]+", REG_EXTENDED | REG_NOSUB) != 0) {
        return;
    }

    while (regexec(&regex, str + pos, nmatch, pmatch, 0) == 0) {
        int match_start = pmatch[0].rm_so + pos;
        int match_end = pmatch[0].rm_eo + pos;

        size_t remaining_space = 1024 - strlen(result);
        if (pos > 0 && (match_start - pos) <= remaining_space) {
            strncat(result, str + pos, match_start - pos);
        }
        pos = match_end;
    }

    size_t length = strlen(str);
    if (pos < length) {
        size_t remaining_space = 1024 - strlen(result);
        if (length - pos <= remaining_space) {
            strncat(result, str + pos, length - pos);
        }
    }

    if (strlen(result) < 1024) {
        snprintf(str, 1024, "%s", result);
    } else {
        strncpy(str, result, 1023);
        str[1023] = '\0';
    }

    regfree(&regex);
}

int main() {
    char input[] = "ThIs iS a TeSt StRiNg";
    remove_lowercase_substrings(input);
    printf("%s\n", input);
    return 0;
}