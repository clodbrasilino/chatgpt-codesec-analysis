#include <stdio.h>
#include <string.h>
#include <ctype.h>

char str[1000], ch;
int i, j, count[26] = {0}, min;

void minimize_string() {
    for(i = 0; str[i] != '\0'; i++) {
        count[tolower(str[i]) - 'a']++;
    }

    min = count[0];
    ch = 'a';

    for(i = 1; i < 26; i++) {
        if(count[i] < min) {
            min = count[i];
            ch = i + 'a';
        }
    }

    for(i = 0; str[i] != '\0'; i++) {
        if(tolower(str[i]) != ch) {
            printf("%c", str[i]);
        }
    }
}

int main() {
    printf("Enter a string: ");
    fgets(str, 1000, stdin);

    minimize_string();

    return 0;
}
