#include <stdio.h>
#include <stddef.h>

void remove_first_last_occurrence(char *str, size_t max_len, char ch) {
    if (str == NULL) {
        return;
    }

    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    
    if (len == max_len) {
        return;
    }

    int first = -1;
    int last = -1;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == ch) {
            if (first == -1) {
                first = (int)i;
            }
            last = (int)i;
        }
    }

    if (first != -1) {
        if (first == last) {
            for (size_t i = first; i < len; i++) {
                str[i] = str[i + 1];
            }
        } else {
            for (size_t i = last; i < len; i++) {
                str[i] = str[i + 1];
            }
            len--; 
            for (size_t i = first; i < len; i++) {
                str[i] = str[i + 1];
            }
        }
    }
}

int main(void) {
    char str1[] = "hello world";
    remove_first_last_occurrence(str1, sizeof(str1), 'l');
    printf("%s\n", str1);

    char str2[] = "programming";
    remove_first_last_occurrence(str2, sizeof(str2), 'r');
    printf("%s\n", str2);

    char str3[] = "abcd";
    remove_first_last_occurrence(str3, sizeof(str3), 'z');
    printf("%s\n", str3);

    char str4[] = "test";
    remove_first_last_occurrence(str4, sizeof(str4), 't');
    printf("%s\n", str4);

    return 0;
}