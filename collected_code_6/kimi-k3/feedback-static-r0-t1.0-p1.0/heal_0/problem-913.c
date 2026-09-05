#include <stdio.h>
#include <string.h>
#include <ctype.h>

int ends_with_number(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }
    
    size_t len = strlen(str);
    size_t i = len - 1;
    
    if (!isdigit((unsigned char)str[i])) {
        return 0;
    }
    
    while (i > 0 && isdigit((unsigned char)str[i - 1])) {
        i--;
    }
    
    return 1;
}

int main(void) {
    const char *test1 = "Hello123";
    const char *test2 = "Hello";
    const char *test3 = "123";
    const char *test4 = "";
    
    printf("%d\n", ends_with_number(test1));
    printf("%d\n", ends_with_number(test2));
    printf("%d\n", ends_with_number(test3));
    printf("%d\n", ends_with_number(test4));
    printf("%d\n", ends_with_number(NULL));
    
    return 0;
}