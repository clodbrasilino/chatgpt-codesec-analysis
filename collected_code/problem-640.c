#include <stdio.h>
#include <string.h>

void remove_parenthesis_area(char* string) {
    int length = strlen(string);
    int i, j = 0;
    int count = 0;

    for (i = 0; i < length; i++) {
        if (string[i] == '(') {
            count++;
        }
        else if (string[i] == ')') {
            count--;
            if (count == 0) {
                continue;
            }
        }

        string[j++] = string[i];
    }

    string[j] = '\0';
}

int main() {
    char string[100] = "This (is) a string (with) parenthesis.";
    remove_parenthesis_area(string);
    printf("%s\n", string);

    return 0;
}