#include <stdio.h>

void remove_lowercase_substrings(char *str) {
    if (str == NULL) {
        return;
    }

    char *src = str;
    char *dst = str;

    while (*src != '\0') {
        if (*src < 'a' || *src > 'z') {
            *dst = *src;
            dst++;
        }
        src++;
    }
    *dst = '\0';
}

int main(void) {
    char str1[] = "Hello world! This IS a TEST.";
    char str2[] = "ALLCAPS";
    char str3[] = "alllower";
    char str4[] = "MiXeD cAsE 123";

    remove_lowercase_substrings(str1);
    remove_lowercase_substrings(str2);
    remove_lowercase_substrings(str3);
    remove_lowercase_substrings(str4);

    printf("%s\n", str1);
    printf("%s\n", str2);
    printf("%s\n", str3);
    printf("%s\n", str4);

    return 0;
}