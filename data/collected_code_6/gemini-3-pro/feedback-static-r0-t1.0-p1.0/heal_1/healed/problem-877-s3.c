#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sortString(char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return;
    }

    size_t length = strnlen(str, max_len);
    if (length <= 1) {
        return;
    }

    for (size_t i = 0; i < length - 1; i++) {
        for (size_t j = i + 1; j < length; j++) {
            if (str[i] > str[j]) {
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

int main(void) {
    char str[] = "programming";
    
    sortString(str, sizeof(str));
    
    printf("%s\n", str);
    
    return 0;
}