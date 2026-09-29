#include <stdio.h>
#include <regex.h>
#include <string.h>

void removeMultipleSpaces(char *str, size_t str_length) {
    if(str == NULL) {
        return;
    }

    regex_t regex;
    regcomp(&regex, "  +", REG_EXTENDED);
    regmatch_t match;

    int len = strnlen(str, str_length);
    int offset = 0;

    while (offset < len && regexec(&regex, str + offset, 1, &match, 0) == 0) {
        int start = match.rm_so + offset;
        int end = match.rm_eo + offset;
        int numSpaces = end - start;
        int numCharsAfterSpaces = len - end;

        if(start + numCharsAfterSpaces < str_length) {
            memmove(str + start, str + end, numCharsAfterSpaces);
            str[len - numSpaces] = '\0';
            len -= numSpaces;
        }
        offset = start + 1;
    }

    regfree(&regex);
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[1024] = "This   is  a    string   with    multiple   spaces.";
    printf("Before removing multiple spaces: %s\n", str);
    removeMultipleSpaces(str, sizeof(str));
    printf("After removing multiple spaces: %s\n", str);

    return 0;
}