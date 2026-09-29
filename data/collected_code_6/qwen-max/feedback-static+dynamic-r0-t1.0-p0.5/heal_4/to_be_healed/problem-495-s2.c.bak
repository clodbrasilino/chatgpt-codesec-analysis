#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void remove_lowercase_substrings(char *str) {
    regex_t regex;
    char result[1024];
    regmatch_t pmatch[1];
    int nmatch = 1;
    int pos = 0;

    if (regcomp(&regex, "[a-z]+", REG_EXTENDED | REG_NOSUB) != 0) {
        return;
    }

    result[0] = '\0';

    /* Possible weaknesses found:
     * ASan: SEGV
     */
    while (regexec(&regex, str + pos, nmatch, pmatch, 0) == 0) {
        int match_start = pmatch[0].rm_so + pos;
        int match_end = pmatch[0].rm_eo + pos;

        int len = match_start - pos;
        if (len > 0 && (strlen(result) + len) < sizeof(result)) {
            strncat(result, str + pos, len);
        }
        pos = match_end;
    }

    if (pos < (int)strlen(str)) {
        int len = strlen(str) - pos;
        if ((strlen(result) + len) < sizeof(result)) {
            strncat(result, str + pos, len);
        }
    }

    strcpy(str, result);
    regfree(&regex);
}

int main() {
    char input[] = "ThIs iS a TeSt StRiNg";
    remove_lowercase_substrings(input);
    printf("%s\n", input);
    return 0;
}