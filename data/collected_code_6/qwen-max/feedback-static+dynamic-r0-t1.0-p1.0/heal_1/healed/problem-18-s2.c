#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_chars(char *str1, const char *str2) {
    char *result = malloc(strlen(str1) + 1);
    int j, k;
    for (int i = 0; str1[i] != '\0'; i++) {
        for (j = 0; str2[j] != '\0'; j++) {
            if (str1[i] == str2[j]) {
                break;
            }
        }
        if (str2[j] == '\0') {
            for (k = 0; result[k] != '\0'; k++);
            result[k] = str1[i];
            result[k + 1] = '\0';
        }
    }
    strcpy(str1, result);
    free(result);
}

int main() {
    char str1[100] = "hello world";
    const char *str2 = "lo";
    remove_chars(str1, str2);
    printf("%s\n", str1);
    return 0;
}