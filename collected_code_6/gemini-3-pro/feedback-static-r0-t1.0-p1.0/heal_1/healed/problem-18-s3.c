#include <stdio.h>
#include <stdlib.h>

void remove_matching_chars(char *str1, const char *str2);

void remove_matching_chars(char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return;
    }

    int flags[256] = {0};
    const unsigned char *u_str2 = (const unsigned char *)str2;
    
    while (*u_str2) {
        flags[*u_str2] = 1;
        u_str2++;
    }

    size_t src = 0;
    size_t dst = 0;
    const unsigned char *u_str1 = (const unsigned char *)str1;

    while (u_str1[src] != '\0') {
        if (!flags[u_str1[src]]) {
            str1[dst] = str1[src];
            dst++;
        }
        src++;
    }
    str1[dst] = '\0';
}

int main(void) {
    char str1[] = "hello world";
    const char *str2 = "ol";

    remove_matching_chars(str1, str2);
    printf("%s\n", str1);

    char str3[] = "programming in C is fun";
    const char *str4 = "aeiou";

    remove_matching_chars(str3, str4);
    printf("%s\n", str3);

    char *null_str = NULL;
    remove_matching_chars(null_str, str4);

    return 0;
}