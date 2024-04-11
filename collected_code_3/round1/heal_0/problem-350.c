#include <stdio.h>
#include <string.h>

#define MAX_CHAR 256

char* minimizeString(char* str) {
    int count[MAX_CHAR] = {0};
    int len = strlen(str), min = len, min_index = -1;
    char* res = (char*)malloc(sizeof(char) * (len + 1));

    for (int i = 0; i < len; i++)
        count[str[i]]++;

    for (int i = 0; i < MAX_CHAR; i++)
        if (count[i] < min && count[i] != 0) {
            min = count[i];
            min_index = i;
        }

    int j = 0;
    for (int i = 0; i < len; i++)
        if (str[i] != min_index)
            res[j++] = str[i];

    res[j] = '\0';

    return res;
}

int main() {
    char str[] = "example string";
    char* res = minimizeString(str);
    printf("%s\n", res);
    free(res);
    return 0;
}