#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool first_last_equal(const char *str) {
    if (str == NULL || str[0] == '\0') {
        return false;
    }
    
    size_t len = strlen(str);
    return str[0] == str[len - 1];
}

int main(void) {
    const char str1[] = "hello";
    const char str2[] = "world";
    const char str3[] = "a";
    const char str4[] = "";
    const char *str5 = NULL;
    
    printf("str1: %d\n", first_last_equal(str1));
    printf("str2: %d\n", first_last_equal(str2));
    printf("str3: %d\n", first_last_equal(str3));
    printf("str4: %d\n", first_last_equal(str4));
    printf("str5: %d\n", first_last_equal(str5));
    
    return 0;
}