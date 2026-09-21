#include <stdio.h>

int checkFirstLastChar(const char *str) {
    if (str == NULL || *str == '\0' || *(str + 1) == '\0') {
        return 0;
    }
    const char *end = str;
    while (*(end + 1) != '\0') {
        end++;
    }
    return *str == *end;
}

int main() {
    const char *test1 = "radar";
    const char *test2 = "hello";
    const char *test3 = "";
    const char *test4 = "a";

    printf("%s: %s\n", test1, checkFirstLastChar(test1) ? "Equal" : "Not Equal");
    printf("%s: %s\n", test2, checkFirstLastChar(test2) ? "Equal" : "Not Equal");
    printf("%s: %s\n", test3, checkFirstLastChar(test3) ? "Equal" : "Not Equal");
    printf("%s: %s\n", test4, checkFirstLastChar(test4) ? "Equal" : "Not Equal");

    return 0;
}