#include <stdio.h>
#include <string.h>
#include <ctype.h>

int hasNumberAtEnd(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    int len = strlen(str);
    if (len == 0) {
        return 0;
    }
    
    return isdigit((unsigned char)str[len - 1]);
}

int main() {
    const char *test1 = "Hello123";
    const char *test2 = "World";
    const char *test3 = "Test0";
    const char *test4 = "";
    const char *test5 = NULL;

    printf("'%s' ends with a number: %d\n", test1, hasNumberAtEnd(test1));
    printf("'%s' ends with a number: %d\n", test2, hasNumberAtEnd(test2));
    printf("'%s' ends with a number: %d\n", test3, hasNumberAtEnd(test3));
    printf("'%s' ends with a number: %d\n", test4, hasNumberAtEnd(test4));
    printf("NULL ends with a number: %d\n", hasNumberAtEnd(test5));

    return 0;
}