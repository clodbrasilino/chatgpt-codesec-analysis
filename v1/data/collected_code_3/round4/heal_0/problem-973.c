#include <stdio.h>
#include <string.h>

void leftRotate(char *str, int d) {
    int len = strlen(str);
    char temp[d];
    strncpy(temp, str, d);
    strcpy(str, str + d);
    strncat(str, temp, d);
}

int main() {
    char str[] = "HelloWorld";
    int d = 2;
    leftRotate(str, d);
    printf("%s", str);
    return 0;
}