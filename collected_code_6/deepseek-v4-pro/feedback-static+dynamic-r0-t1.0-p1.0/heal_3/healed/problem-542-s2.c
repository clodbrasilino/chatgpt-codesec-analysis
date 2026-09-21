#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define ERROR_BUF_SIZE 256

static void replace_chars(char *str, size_t str_size) {
    regex_t regex;
    regmatch_t match;
    char *src = str;
    char *dst = str;
    int result;
    
    if (str == NULL || str_size == 0) {
        return;
    }
    
    result = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    
    if (result != 0) {
        char error_buf[ERROR_BUF_SIZE];
        regerror(result, &regex, error_buf, sizeof(error_buf));
        fprintf(stderr, "Regex compilation failed: %s\n", error_buf);
        return;
    }
    
    while (*src != '\0') {
        if (regexec(&regex, src, 1, &match, 0) == 0 && match.rm_so == 0) {
            if ((size_t)(dst - str) + 2 > str_size) {
                break;
            }
            *dst++ = ':';
            src += match.rm_eo;
        } else {
            if ((size_t)(dst - str) + 2 > str_size) {
                break;
            }
            *dst++ = *src++;
        }
    }
    *dst = '\0';
    
    regfree(&regex);
}

int main(void) {
    char str1[] = "Hello, world. This is a test";
    char str2[] = "one,two.three four";
    char str3[] = "NoDelimitersHere";
    
    printf("Before: %s\n", str1);
    replace_chars(str1, sizeof(str1));
    printf("After:  %s\n\n", str1);
    
    printf("Before: %s\n", str2);
    replace_chars(str2, sizeof(str2));
    printf("After:  %s\n\n", str2);
    
    printf("Before: %s\n", str3);
    replace_chars(str3, sizeof(str3));
    printf("After:  %s\n", str3);
    
    return 0;
}