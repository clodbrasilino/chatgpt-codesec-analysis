#include <stdio.h>
#include <ctype.h>

void remove_non_alphanumeric(char *str) {
    if (str == NULL) {
        return;
    }

    char *dest = str;
    char *src = str;

    while (*src != '\0') {
        if (isalnum((unsigned char)*src)) {
            *dest = *src;
            dest++;
        }
        src++;
    }

    *dest = '\0';
}

int main(void) {
    char str1[] = "Hello, World! 123";
    remove_non_alphanumeric(str1);
    printf("%s\n", str1);

    char str2[] = "@#@#Test_123!!!";
    remove_non_alphanumeric(str2);
    printf("%s\n", str2);

    char str3[] = "!@#$%^&*()";
    remove_non_alphanumeric(str3);
    printf("%s\n", str3);

    remove_non_alphanumeric(NULL);

    return 0;
}