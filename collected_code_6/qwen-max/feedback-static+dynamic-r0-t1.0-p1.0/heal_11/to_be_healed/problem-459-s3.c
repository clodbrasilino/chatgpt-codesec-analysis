#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void remove_uppercase_substrings(char *str) {
    static const char *pattern = "[A-Z]+";
    regex_t regex;
    regmatch_t pmatch;

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NEWLINE))
        return;

    int pos = 0;
    while (1) {
        int rc = regexec(&regex, str + pos, 1, &pmatch, 0);
        if (rc == REG_NOMATCH)
            break;

        if (pmatch.rm_so >= 0 && pmatch.rm_eo > pmatch.rm_so) {
            size_t offset = pmatch.rm_so + pos;
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            memmove(str + offset, str + offset + (pmatch.rm_eo - pmatch.rm_so), strlen(str + offset + (pmatch.rm_eo - pmatch.rm_so)) + 1);
            pos += pmatch.rm_so;
        } else {
            if (str[pos] != '\0')
                pos++;
            else
                break;
        }
    }

    regfree(&regex);
}

int main() {
    char input[] = "Hello World! ThIs Is a TeSt.";
    remove_uppercase_substrings(input);
    printf("%s\n", input);
    return 0;
}