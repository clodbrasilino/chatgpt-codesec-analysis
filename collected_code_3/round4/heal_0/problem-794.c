#include <stdio.h>
#include <string.h>

int match(char str[]) {
    int len = strlen(str);
    int i, flag = 0;
    for(i = 0; i < len; i++) {
        if(str[i] == 'a') {
            flag = 1;
        }
        if(flag == 1 && str[i] == 'b' && i == len - 1) {
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