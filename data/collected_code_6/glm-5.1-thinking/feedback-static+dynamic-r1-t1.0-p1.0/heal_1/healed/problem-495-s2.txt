#include <stdio.h>

void remove_lowercase(char *str) {
    if (str == NULL) {
        return;
    }
    
    char *dst = str;
    char *src = str;
    
    while (*src) {
        if (*src < 'a' || *src > 'z') {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

int main(void) {
    char s1[] = "HelloWorld";
    char s2[] = "abcDEFghiJKL";
    char s3[] = "XYZ";
    char s4[] = "xyz";

    remove_lowercase(s1);
    remove_lowercase(s2);
    remove_lowercase(s3);
    remove_lowercase(s4);

    printf("%s\n", s1);
    printf("%s\n", s2);
    printf("%s\n", s3);
    printf("%s\n", s4);

    return 0;
}