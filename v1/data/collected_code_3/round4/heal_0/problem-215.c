#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* decode(const char* str) {
    int len = strlen(str);
    char* result = (char*)malloc(sizeof(char) * len * 2);
    int i, j = 0, count;
    char num[10], ch;

    for(i = 0; i < len; i++) {
        count = 0;
        if(str[i] >= '0' && str[i] <= '9') {
            while(str[i] >= '0' && str[i] <= '9') {
                num[count++] = str[i++];
            }
            num[count] = '\0';
            count = atoi(num);
            ch = str[i];
            while(count--) {
                result[j++] = ch;
            }
        }
    }
    result[j] = '\0';
    return result;
}

int main() {
    char str[] = "9A4B2C3D";
    char* result = decode(str);
    printf("%s\n", result);
    free(result);
    return 0;
}