#include <stdio.h>
#include <string.h>
#include <ctype.h>

int ends_with_number(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }

    const char *end = str + len - 1;

    while (end >= str && isspace((unsigned char)*end)) {
        end--;
    }

    if (end < str) {
        return 0;
    }

    if (isdigit((unsigned char)*end)) {
        while (end >= str && isdigit((unsigned char)*end)) {
            end--;
        }
        if (end < str || !isalpha((unsigned char)*end)) {
            return 0;
        }
        return 1;
    }

    return 0;
}

int main(void) {
    const char *test1 = "abc123";
    const char *test2 = "abc";
    const char *test3 = "123";
    const char *test4 = "abc123 ";
    const char *test5 = "";
    const char *test6 = NULL;
    const char *test7 = "abc!123";
    const char *test8 = "abc 123";
    
    int result1 = ends_with_number(test1);
    int result2 = ends_with_number(test2);
    int result3 = ends_with_number(test3);
    int result4 = ends_with_number(test4);
    int result5 = ends_with_number(test5);
    int result6 = ends_with_number(test6);
    int result7 = ends_with_number(test7);
    int result8 = ends_with_number(test8);

    printf("%s: %d\n", test1 ? test1 : "NULL", result1);
    printf("%s: %d\n", test2 ? test2 : "NULL", result2);
    printf("%s: %d\n", test3 ? test3 : "NULL", result3);
    printf("%s: %d\n", test4 ? test4 : "NULL", result4);
    printf("%s: %d\n", test5 ? test5 : "NULL", result5);
    printf("%s: %d\n", test6 ? test6 : "NULL", result6);
    printf("%s: %d\n", test7 ? test7 : "NULL", result7);
    printf("%s: %d\n", test8 ? test8 : "NULL", result8);

    return 0;
}