#include <stdio.h>
#include <string.h>

void replaceSpaces(char *str) {
    int count = 0, i;
    for (i = 0; str[i]; i++)
        if (str[i] == ' ')
            count++;
    int new_length = i + count * 2 + 1;
    char new_str[new_length];
    int j = 0;
    for (i = 0; str[i]; i++) {
        if (str[i] == ' ') {
            new_str[j] = '%';
            new_str[j + 1] = '2';
            new_str[j + 2] = '0';
            j = j + 3;
        } else {
            new_str[j] = str[i];
            j++;
        }
    }
    new_str[j] = '\0';
    strcpy(str, new_str);
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, 100, stdin);
    str[strlen(str) - 1] = '\0';
    replaceSpaces(str);
    printf("Modified string: %s\n", str);
    return 0;
}