#include <stdio.h>
#include <string.h>

void replace_multiple_occurrence(char *str) {
    if (str == NULL) {
        return;
    }

    int len = strlen(str);
    if (len < 2) {
        return;
    }

    int write_index = 0;
    for (int read_index = 0; read_index < len; read_index++) {
        if (read_index == 0 || str[read_index] != str[read_index - 1]) {
            str[write_index++] = str[read_index];
        }
    }
    str[write_index] = '\0';
}

int main(void) {
    char str1[] = "aaabbbcccaaa";
    replace_multiple_occurrence(str1);
    printf("%s\n", str1);

    char str2[] = "hello";
    replace_multiple_occurrence(str2);
    printf("%s\n", str2);

    char str3[] = "a";
    replace_multiple_occurrence(str3);
    printf("%s\n", str3);

    char str4[] = "";
    replace_multiple_occurrence(str4);
    printf("%s\n", str4);

    char str5[] = "aaAAbb";
    replace_multiple_occurrence(str5);
    printf("%s\n", str5);

    replace_multiple_occurrence(NULL);

    return 0;
}