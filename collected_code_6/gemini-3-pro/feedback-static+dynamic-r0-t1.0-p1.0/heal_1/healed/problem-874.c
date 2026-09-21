#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool isConcatenation(const char *str) {
    if (str == NULL) {
        return false;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    if (len == 0) {
        return false;
    }

    for (size_t i = 1; i <= len / 2; ++i) {
        if (len % i == 0) {
            bool match = true;
            for (size_t j = i; j < len; j += i) {
                if (strncmp(str, str + j, i) != 0) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return true;
            }
        }
    }

    return false;
}

int main(void) {
    const char *test1 = "abcabc";
    const char *test2 = "ababab";
    const char *test3 = "abcdef";
    const char *test4 = "";
    
    printf("'%s': %s\n", test1, isConcatenation(test1) ? "true" : "false");
    printf("'%s': %s\n", test2, isConcatenation(test2) ? "true" : "false");
    printf("'%s': %s\n", test3, isConcatenation(test3) ? "true" : "false");
    printf("'%s': %s\n", test4, isConcatenation(test4) ? "true" : "false");

    return 0;
}