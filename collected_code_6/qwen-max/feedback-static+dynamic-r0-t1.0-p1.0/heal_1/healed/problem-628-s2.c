#include <stdio.h>
#include <string.h>

void replace_spaces(char *str, size_t n) {
    if (str == NULL) return;

    int i, count = 0;
    for (i = 0; i < n && str[i] != '\0'; i++) {
        if (str[i] == ' ') count++;
    }

    int original_length = i;
    int new_length = original_length + (count * 2);
    if (new_length > n) return;

    str[new_length--] = '\0';

    for (i = original_length - 1; i >= 0; i--) {
        if (str[i] == ' ') {
            str[new_length--] = '0';
            str[new_length--] = '2';
            str[new_length--] = '%';
        } else {
            str[new_length--] = str[i];
        }
    }
}

int main() {
    char str1[] = "Mr John Smith    ";
    replace_spaces(str1, sizeof(str1));
    printf("Replaced string: %s\n", str1);

    char str2[] = " Test String with Spaces  ";
    replace_spaces(str2, sizeof(str2));
    printf("Replaced string: %s\n", str2);

    return 0;
}