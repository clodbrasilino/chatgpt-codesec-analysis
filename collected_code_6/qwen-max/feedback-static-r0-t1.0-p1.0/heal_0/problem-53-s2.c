#include <stdio.h>
#include <string.h>

int checkFirstLastCharEqual(const char *str) {
    if (str == NULL || str[0] == '\0' || str[strlen(str) - 1] == '\0') {
        return 0;
    }
    return str[0] == str[strlen(str) - 1];
}

int main() {
    const char *test1 = "radar";
    const char *test2 = "hello";
    const char *test3 = "";
    const char *test4 = "a";

    printf("%s: %s\n", test1, (checkFirstLastCharEqual(test1) ? "Equal" : "Not Equal"));
    printf("%s: %s\n", test2, (checkFirstLastCharEqual(test2) ? "Equal" : "Not Equal"));
    printf("%s: %s\n", test3, (checkFirstLastCharEqual(test3) ? "Equal" : "Not Equal"));
    printf("%s: %s\n", test4, (checkFirstLastCharEqual(test4) ? "Equal" : "Not Equal"));

    return 0;
}