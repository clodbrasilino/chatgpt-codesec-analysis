#include <stdio.h>
#include <string.h>

void left_rotate(char *str, int d) {
    int n = strlen(str);
    /* Possible weaknesses found:
     *  Division by zero
     *  Either the condition 'n==0' is redundant or there is division by zero at line 6. [zerodivcond]
     */
    d = d % n;
    /* Possible weaknesses found:
     *  Assuming that condition 'n==0' is not redundant
     */
    if (d == 0 || n == 0) {
        return;
    }
    char temp[d];
    strncpy(temp, str, d);
    memmove(str, str + d, n - d + 1);
    strcat(str, temp);
}

int main() {
    char str[] = "abcdef";
    int d = 2;
    left_rotate(str, d);
    printf("%s\n", str);
    return 0;
}