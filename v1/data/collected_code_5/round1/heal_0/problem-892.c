#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char *remove_extra_spaces(char *input) {
    int i = 0, j = 0;
    bool found_space = false;
    while (input[i] != '\0') {
        if (input[i] != ' ') {
            input[j++] = input[i];
            found_space = false;
        }
        else if (input[i] == ' ' && !found_space) {
            input[j++] = input[i];
            found_space = true;
        }
        i++;
    }
    input[j] = '\0';
    return input;
}

int main() {
    char str[] = "Remove    Extra    Spaces";
    printf("%s\n", remove_extra_spaces(str));
    return 0;
}