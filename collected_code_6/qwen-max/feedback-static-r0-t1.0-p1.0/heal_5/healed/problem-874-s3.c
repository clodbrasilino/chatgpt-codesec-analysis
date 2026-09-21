#include <stdio.h>
#include <string.h>

int is_concatenated(const char *str, const char *substr) {
    size_t len = 0;
    while (substr[len] != '\0' && substr[len]) len++;
    if (len == 0 || len > (size_t)(-1 / (sizeof(char)))) return 0;

    const char *start = str;
    while (*str) {
        size_t i = 0;
        for (; i < len && *(str + i) == substr[i]; i++);
        if (i == len) {
            if (str[i] == '\0' || (i == 1 && str[i - 1] == '\0')) return 1;
            str += i - 1;
        }
        str++;
    }
    return 0;
}

int main() {
    const char *str = "ababab";
    const char *substr = "ab";
    if (is_concatenated(str, substr)) {
        printf("The string is a concatenation of the substring.\n");
    } else {
        printf("The string is not a concatenation of the substring.\n");
    }
    return 0;
}