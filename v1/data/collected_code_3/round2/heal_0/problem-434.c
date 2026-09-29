#include <stdio.h>
#include <string.h>

int match(char *str) {
    int length = strlen(str);
    int i, flag = 0, count = 0;

    for(i = 0; i < length; i++) {
        if(str[i] == 'a') {
            flag = 1;
        }
        if(flag == 1 && str[i] == 'b') {
            count++;
        }
    }

    if(flag == 1 && count > 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);

    if(match(str)) {
        printf("The string matches the pattern\n");
    } else {
        printf("The string does not match the pattern\n");
    }

    return 0;
}