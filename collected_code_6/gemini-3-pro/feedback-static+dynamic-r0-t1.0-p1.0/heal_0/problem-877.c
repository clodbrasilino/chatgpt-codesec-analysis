#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort_string(char *str) {
    if (str == NULL) {
        return;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return;
    }

    for (size_t i = 0; i < len - 1; i++) {
        for (size_t j = i + 1; j < len; j++) {
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
    
    sort_string(str);
    
    printf("%s\n", str);
    
    return 0;
}