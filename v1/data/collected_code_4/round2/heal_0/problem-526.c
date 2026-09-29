#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void capitalizeFirstAndLast(char* str) {
    bool newWord = true;
    int len = strlen(str);

    for(int i = 0; i < len; i++) {
        if(isspace(str[i])) {
            newWord = true;
        } else {
            if(newWord) {
                str[i] = toupper(str[i]);
                newWord = false;
            }

            if(!isspace(str[i]) && (isspace(str[i+1]) || str[i+1] == '\0')) {
                str[i] = toupper(str[i]);
            }
        }
    }
}

int main() {
    char str[100];
    printf("Enter a sentence: ");
    fgets(str, sizeof(str), stdin);

    // remove newline at the end of the string
    str[strcspn(str, "\n")] = 0;

    capitalizeFirstAndLast(str);
    printf("%s\n", str);

    return 0;
}