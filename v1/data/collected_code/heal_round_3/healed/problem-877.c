#include <stdio.h>
#include <string.h>
#include <stddef.h>

void sortString(char *str, size_t len) {
    if(str == NULL || len <= 1)
        return;

    char temp;

    for (size_t i = 0; i < len - 1; i++) {
        for (size_t j = i + 1; j < len; j++) {
            if (str[i] > str[j]) {
                temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

int main() {
    char str[] = "example";
    size_t len = sizeof(str)/sizeof(char);

    sortString(str, len);
    printf("Sorted string: %s\n", str);

    return 0;
}