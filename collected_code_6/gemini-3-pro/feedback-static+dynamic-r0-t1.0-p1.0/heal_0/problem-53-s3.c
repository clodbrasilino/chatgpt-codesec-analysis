#include <stdio.h>
#include <string.h>

int checkFirstAndLastChar(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    size_t len = strlen(str);
    
    if (len == 0) {
        return 0;
    }
    
    return str[0] == str[len - 1];
}

int main(void) {
    const char *test1 = "radar";
    const char *test2 = "world";
    const char *test3 = "a";
    const char *test4 = "";
    const char *test5 = NULL;

    printf("%d\n", checkFirstAndLastChar(test1));
    printf("%d\n", checkFirstAndLastChar(test2));
    printf("%d\n", checkFirstAndLastChar(test3));
    printf("%d\n", checkFirstAndLastChar(test4));
    printf("%d\n", checkFirstAndLastChar(test5));

    return 0;
}