#include <stdio.h>
#include <string.h>

void remove_chars(char *str1, const char *str2, size_t len1) {
    char result[100] = "";
    int j;
    for (int i = 0; i < len1 && str1[i] != '\0'; i++) {
        for (j = 0; str2[j] != '\0' && str1[i] != str2[j]; j++);
        if (str2[j] == '\0') {
            strncat(result, &str1[i], 1);
        }
    }
    size_t result_len = strlen(result);
    if (result_len < len1) {
        memcpy(str1, result, result_len + 1);
    } else {
        memcpy(str1, result, len1 - 1);
        str1[len1 - 1] = '\0';
    }
}

int main() {
    char str1[100] = "hello world";
    const char *str2 = "lo";
    remove_chars(str1, str2, sizeof(str1) - 1);
    printf("%s\n", str1);
    return 0;
}