#include <stdio.h>
#include <string.h>

void remove_first_last_occurrence(char *str, char ch) {
    if (str == NULL || *str == '\0') {
        return;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    if (len == 0) {
        return;
    }

    int first = -1, last = -1;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == ch) {
            if (first == -1) {
                first = (int)i;
            }
            last = (int)i;
        }
    }

    if (first == -1) {
        return;
    }

    if (first == last) {
        size_t write_idx = 0;
        for (size_t i = 0; i < len; i++) {
            if ((int)i == first) {
                continue;
            }
            str[write_idx++] = str[i];
        }
        str[write_idx] = '\0';
        return;
    }

    size_t write_idx = 0;
    for (size_t i = 0; i < len; i++) {
        if ((int)i == first || (int)i == last) {
            continue;
        }
        str[write_idx++] = str[i];
    }
    str[write_idx] = '\0';

    if (write_idx > 0) {
        size_t final_len = write_idx;
        for (size_t i = final_len; i < len; i++) {
            str[i] = '\0';
        }
    }
}

int main(void) {
    char str1[] = "hello world";
    remove_first_last_occurrence(str1, 'o');
    printf("%s\n", str1);

    char str2[] = "aaaa";
    remove_first_last_occurrence(str2, 'a');
    printf("%s\n", str2);

    char str3[] = "abcdef";
    remove_first_last_occurrence(str3, 'z');
    printf("%s\n", str3);

    char str4[] = "a";
    remove_first_last_occurrence(str4, 'a');
    printf("%s\n", str4);

    char str5[] = "";
    remove_first_last_occurrence(str5, 'a');
    printf("%s\n", str5);

    return 0;
}