#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void replace_spaces_with_percent_20(char *str) {
    if (str == NULL) return;

    int space_count = 0, i;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') space_count++;
    }

    int new_length = i + space_count * 2;
    char *new_str = (char *)malloc(new_length + 1);
    if (new_str == NULL) return;

    for (i = 0; i < new_length;) {
        if (str[i] == ' ') {
            new_str[i++] = '%';
            new_str[i++] = '2';
            new_str[i++] = '0';
        } else {
            new_str[i] = str[i];
            i++;
        }
    }
    new_str[new_length] = '\0';

    for (i = 0; i <= new_length; i++) {
        str[i] = new_str[i];
    }
    free(new_str);
}

int main() {
    char input[] = "Hello World This is a Test";
    replace_spaces_with_percent_20(input);
    printf("%s\n", input);
    return 0;
}