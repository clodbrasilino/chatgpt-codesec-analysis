#include <stdio.h>
#include <string.h>
#include <regex.h>

void remove_lowercase(char *str) {
    if (str == NULL) {
        return;
    }

    regex_t regex;
    if (regcomp(&regex, "[a-z]+", REG_EXTENDED) != 0) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    size_t shift = 0;
    size_t offset = 0;
    regmatch_t match;

    while (offset < len) {
        if (regexec(&regex, str + offset, 1, &match, 0) == REG_NOMATCH) {
            break;
        }

        if (match.rm_so > 0) {
            memmove(str + shift, str + offset + match.rm_so, match.rm_so);
            shift += match.rm_so;
        }

        offset += match.rm_eo;
    }

    memmove(str + shift, str + offset, len - offset + 1);

    regfree(&regex);
}

int main(void) {
    char s1[] = "HelloWorld";
    char s2[] = "abcDEFghiJKL";
    char s3[] = "XYZ";
    char s4[] = "xyz";

    remove_lowercase(s1);
    remove_lowercase(s2);
    remove_lowercase(s3);
    remove_lowercase(s4);

    printf("%s\n", s1);
    printf("%s\n", s2);
    printf("%s\n", s3);
    printf("%s\n", s4);

    return 0;
}