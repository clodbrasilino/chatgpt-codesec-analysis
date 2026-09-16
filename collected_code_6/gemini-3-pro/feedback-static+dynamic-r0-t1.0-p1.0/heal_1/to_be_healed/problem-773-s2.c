#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void find_substrings(const char *str, const char *sub) {
    if (str == NULL || sub == NULL || *sub == '\0') {
        return;
    }

    int count = 0;
    const char *tmp = str;

    while ((tmp = strstr(tmp, sub)) != NULL) {
        /* Possible weaknesses found:
         *  %ld in format string (no. 2) requires 'long' but the argument type is 'ptrdiff_t {aka signed int}'. [invalidPrintfArgType_sint]
         */
        printf("Occurrence %d: Position %ld\n", ++count, tmp - str);
        tmp++;
    }

    if (count == 0) {
        printf("Substring not found.\n");
    }
}

int main(void) {
    const char *text = "this is a test string for testing the test function";
    const char *substring = "test";

    find_substrings(text, substring);

    return 0;
}