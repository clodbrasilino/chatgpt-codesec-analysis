#include <stdio.h>
#include <string.h>
#include <ctype.h>

void move_numbers(char *str, size_t str_len) {
    char result[200] = "";
    char temp[200] = "";
    int j = 0, k = 0;

    for (int i = 0; i < str_len && str[i] != '\0'; i++) {
        if (isdigit((unsigned char)str[i])) {
            result[j++] = str[i];
        } else {
            temp[k++] = str[i];
        }
    }

    snprintf(result + j, sizeof(result) - j, "%s", temp);
    snprintf(str, str_len, "%s", result);
}

int main() {
    char str[] = "a2b3c4d5e6";
    move_numbers(str, sizeof(str));
    printf("%s\n", str);
    return 0;
}