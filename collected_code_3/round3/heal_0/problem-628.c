#include <stdio.h>
#include <string.h>

void replaceSpaces(char *str) {
    int count = 0, i;
    for (i = 0; str[i]; i++)
        if (str[i] == ' ')
            count++;
    int new_length = i + count * 2 + 1;
    str[new_length] = '\0';
    for (int j = i - 1; j >= 0; j--) {
        if (str[j] == ' ') {
            str[new_length - 1] = '0';
            str[new_length - 2] = '2';
            str[new_length - 3] = '%';
            new_length = new_length - 3;
        } else {
            str[new_length - 1] = str[j];
            new_length--;
        }
    }
}

int main() {
    char str[100] = "Hello World!";
    replaceSpaces(str);
    printf("%s", str);
    return 0;
}