#include <stdio.h>
#include <string.h>
#include <ctype.h>

void capitalizeFirstLast(char *str, size_t strSize) {
    if (str == NULL || strSize == 0) return;
    for (size_t i = 0; i < strSize; ++i) {
        if (i == 0 || (i > 0 && str[i - 1] == ' ')) {
            str[i] = toupper((unsigned char)str[i]);
        } else if (i + 1 < strSize && str[i] == ' ' && str[i + 1] != ' ') {
            str[i + 1] = toupper((unsigned char)str[i + 1]);
        }
    }
    if (strSize > 0 && str[strSize - 2] != ' ') {
        str[strSize - 1] = toupper((unsigned char)str[strSize - 1]);
    }
}

int main() {
    char str[] = "hello world this is a test";
    capitalizeFirstLast(str, sizeof(str) - 1);
    printf("%s\n", str);
    return 0;
}