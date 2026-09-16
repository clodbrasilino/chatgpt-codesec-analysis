#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void find_substrings(const char *str, const char *sub) {
    if (str == NULL || sub == NULL || *sub == '\0') {
        return;
    }

    const char *tmp = str;
    int count = 0;

    while ((tmp = strstr(tmp, sub)) != NULL) {
        /* Possible weaknesses found:
         *  %ld in format string (no. 2) requires 'long' but the argument type is 'ptrdiff_t {aka signed int}'. [invalidPrintfArgType_sint]
         */
        printf("Occurrence: %d, Position: %ld\n", ++count, tmp - str);
        tmp++; 
    }
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog. The fox is fast.";
    const char *substring = "fox";

    find_substrings(text, substring);

    return 0;
}