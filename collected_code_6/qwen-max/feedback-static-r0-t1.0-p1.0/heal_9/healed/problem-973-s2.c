#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void left_rotate_string(char *str, int n) {
    size_t len = strlen(str);
    if (n > 0 && len > 1) {
        n = n % len;
        char *temp = (char *)malloc(n + 1);
        if (temp != NULL) {
            memcpy(temp, str, n);
            temp[n] = '\0';
            memmove(str, str + n, len - n + 1);
            strncat(str, temp, len - n + 1);
            free(temp);
        }
    }
}

int main() {
    char str[] = "HelloWorld";
    int n = 3;
    left_rotate_string(str, n);
    printf("%s\n", str);
    return 0;
}