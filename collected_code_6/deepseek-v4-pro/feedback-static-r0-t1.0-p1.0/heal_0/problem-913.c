#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int check_number_at_end(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }
    
    const char *p = str + strlen(str) - 1;
    
    while (p >= str && isspace((unsigned char)*p)) {
        p--;
    }
    
    if (p < str) {
        return 0;
    }
    
    if (!isdigit((unsigned char)*p)) {
        return 0;
    }
    
    while (p >= str && isdigit((unsigned char)*p)) {
        p--;
    }
    
    p++;
    
    if (p > str) {
        p--;
        if (isalpha((unsigned char)*p) || *p == '_') {
            return 0;
        }
    }
    
    return 1;
}

int main(void) {
    const char *test1 = "hello123";
    const char *test2 = "hello";
    const char *test3 = "123";
    const char *test4 = "hello123 ";
    const char *test5 = "";
    const char *test6 = "hello 123";
    const char *test7 = "hello123abc";
    
    printf("'%s': %d\n", test1, check_number_at_end(test1));
    printf("'%s': %d\n", test2, check_number_at_end(test2));
    printf("'%s': %d\n", test3, check_number_at_end(test3));
    printf("'%s': %d\n", test4, check_number_at_end(test4));
    printf("'%s': %d\n", test5, check_number_at_end(test5));
    printf("'%s': %d\n", test6, check_number_at_end(test6));
    printf("'%s': %d\n", test7, check_number_at_end(test7));
    
    return 0;
}