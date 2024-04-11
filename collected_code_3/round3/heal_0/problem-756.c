#include <stdio.h>
#include <string.h>

int match(char *str) {
    int i, len = strlen(str);
    for(i = 0; i < len; i++) {
        if(str[i] == 'a') {
            if(i < len - 1 && str[i+1] == 'b') {
                i++;
            }
            return 1;
        }
    }
    return 0;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);
    if(match(str)) {
        printf("Matched\n");
    } else {
        printf("Not Matched\n");
    }
    return 0;
}