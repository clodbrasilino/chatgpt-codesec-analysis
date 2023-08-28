#include <stdio.h>
#include <regex.h>

void removeMultipleSpaces(char* str) {
    regex_t regex;
    regcomp(&regex, "  +", REG_EXTENDED);

    regmatch_t match;
    int offset = 0;
    int len = strlen(str);
    while (offset < len && regexec(&regex, str + offset, 1, &match, 0) == 0) {
        int start = match.rm_so + offset;
        int end = match.rm_eo + offset;

        int numSpaces = end - start;
        int numCharsAfterSpaces = len - end;
        memmove(str + start, str + end, numCharsAfterSpaces);
        memset(str + len - numSpaces, ' ', numSpaces);

        len -= numSpaces;
        offset = start + 1;
    }

    regfree(&regex);
}

int main() {
    char str[] = "This   is  a    string   with    multiple   spaces.";
    printf("Before removing multiple spaces: %s\n", str);

    removeMultipleSpaces(str);
    printf("After removing multiple spaces: %s\n", str);

    return 0;
}