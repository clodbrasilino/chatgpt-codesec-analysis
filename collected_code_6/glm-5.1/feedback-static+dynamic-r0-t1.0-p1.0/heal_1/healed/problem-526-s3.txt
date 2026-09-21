#include <stdio.h>
#include <ctype.h>
#include <string.h>

size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

char *capitalize_first_last(char *str, size_t buffer_size) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = safe_strlen(str, buffer_size);
    if (len == 0) {
        return str;
    }

    size_t i = 0;
    while (i < len) {
        if (isalpha((unsigned char)str[i])) {
            size_t start = i;
            while (i < len && isalpha((unsigned char)str[i])) {
                i++;
            }
            size_t end = i - 1;

            if (islower((unsigned char)str[start])) {
                str[start] = (char)toupper((unsigned char)str[start]);
            }

            if (start != end) {
                if (islower((unsigned char)str[end])) {
                    str[end] = (char)toupper((unsigned char)str[end]);
                }
            }
        } else {
            i++;
        }
    }

    return str;
}

int main(void) {
    char str1[] = "hello world";
    char str2[] = "c programming is fun";
    char str3[] = "a";
    char str4[] = "  multiple   spaces  ";

    printf("%s\n", capitalize_first_last(str1, sizeof(str1)));
    printf("%s\n", capitalize_first_last(str2, sizeof(str2)));
    printf("%s\n", capitalize_first_last(str3, sizeof(str3)));
    printf("%s\n", capitalize_first_last(str4, sizeof(str4)));

    return 0;
}