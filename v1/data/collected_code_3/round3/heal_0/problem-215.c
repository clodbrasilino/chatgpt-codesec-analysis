#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* decode(char* str) {
    int len = strlen(str);
    char* result = (char*)malloc(sizeof(char) * len * 10);
    int count = 0;
    int j = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            count = count * 10 + (str[i] - '0');
        } else {
            while (count > 0) {
                result[j++] = str[i];
                count--;
            }
        }
    }
    result[j] = '\0';
    return result;
}

int main() {
    char str[] = "2a3b4c";
    char* decoded_str = decode(str);
    printf("%s\n", decoded_str);
    free(decoded_str);
    return 0;
}