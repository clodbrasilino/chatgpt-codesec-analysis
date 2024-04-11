#include <stdio.h>
#include <string.h>

int match(char *str) {
    int i, length = strlen(str);
    for(i = 0; i < length; i++) {
        if(str[i] == 'a') {
            if(str[i+1] == 'b' || str[i+1] == '\0' || str[i+1] != 'b') {
                return 1;
            }
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