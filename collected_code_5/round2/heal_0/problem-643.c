#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool match(char *str) {
    int len = strlen(str);

    if (len <= 2) {
        return false;
    }

    for (int i = 1; i < len - 1; i++) {
        if (str[i] == 'z') {
            return true;
        }
    }

    return false;
}

int main() {
    char word[20];

    printf("Enter a word: ");
    scanf("%s", word);

    if(match(word)) {
        printf("The word contains 'z' not at the first or last position\n");
    } else {
        printf("The word doesn't contain 'z' in the middle\n");
    }

    return 0;
}