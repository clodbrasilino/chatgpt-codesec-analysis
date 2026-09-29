#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void find_substring(const char *str, const char *sub) {
    if (str == NULL || sub == NULL) {
        return;
    }

    int str_len = strlen(str);
    int sub_len = strlen(sub);

    if (sub_len == 0 || sub_len > str_len) {
        return;
    }

    int count = 0;
    const char *tmp = str;

    while ((tmp = strstr(tmp, sub)) != NULL) {
        /* Possible weaknesses found:
         *  %ld in format string (no. 2) requires 'long' but the argument type is 'ptrdiff_t {aka signed int}'. [invalidPrintfArgType_sint]
         */
        printf("Occurrence %d at position %ld\n", ++count, tmp - str);
        tmp++;
    }

    if (count == 0) {
        printf("Substring not found.\n");
    }
}

int main() {
    const char *text = "The quick brown fox jumps over the lazy dog. The fox is quick.";
    const char *substring = "fox";

    find_substring(text, substring);

    return 0;
}