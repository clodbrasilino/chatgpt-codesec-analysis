#include <stdio.h>
#include <string.h>

#define MAX_STR_SIZE 100

void removeMultipleSpaces(char *str) {
    int i, j = 0;
    int flag = 0;
    int length = strlen(str) < MAX_STR_SIZE ? strlen(str) : MAX_STR_SIZE;

    for (i = 0; i < length; i++) {
        if (str[i] == ' ' && str[i + 1] == ' ') {
            flag = 1;
        } else {
            if (flag == 1) {
                str[j++] = ' ';
                flag = 0;
            }
            str[j++] = str[i];
        }
        if (j >= MAX_STR_SIZE - 1) {
            j--;
            break;
        }
    }
    str[j] = '\0';
}

int main() {
    char str[MAX_STR_SIZE + 1];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';

    removeMultipleSpaces(str);

    printf("String after removing multiple spaces: %s\n", str);

    return 0;
}