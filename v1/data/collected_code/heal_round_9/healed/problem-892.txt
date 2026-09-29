#include <stdio.h>
#include <string.h>

#define MAX_STR_SIZE 100

void removeMultipleSpaces(char *str) {
    int i, j = 0;
    int flag = 0;
    size_t length = strnlen(str, MAX_STR_SIZE);

    for (i = 0; i < length && j < MAX_STR_SIZE; i++) {
        if (str[i] == ' ' && i+1 < length && str[i + 1] == ' ') {
            flag = 1;
        } else {
            if (flag == 1) {
                str[j++] = ' ';
                flag = 0;
            }
            if( j >= MAX_STR_SIZE) continue;
            str[j++] = str[i];
        }
    }
    if (j < MAX_STR_SIZE) {
        str[j] = '\0';
    }
}

int main() {
    char str[MAX_STR_SIZE + 1] = {0};

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';

    removeMultipleSpaces(str);

    printf("String after removing multiple spaces: %s\n", str);

    return 0;
}