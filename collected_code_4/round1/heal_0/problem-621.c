#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* incrementValuesInString(char* str, int k) {
    if (!str) {
        return NULL;
    }
    
    size_t len = strlen(str);
    char* result = (char*)malloc((len + 1) * sizeof(char));
    
    if (!result) {
        return NULL;
    }

    for (size_t i = 0; i < len; ++i) {
        if (isdigit((unsigned char)str[i])) {
            int num = str[i] - '0';
            num = (num + k) % 10;
            result[i] = num + '0';
        } else {
            result[i] = str[i];
        }
    }

    result[len] = '\0';
    return result;
}

int main() {
    char str[] = "abc1efg2hij3";
    int k = 5;
    char* result = incrementValuesInString(str, k);
    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("Memory allocation failed\n");
    }
    return 0;
}