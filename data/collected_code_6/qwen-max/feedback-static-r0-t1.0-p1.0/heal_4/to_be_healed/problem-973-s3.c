#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'memmove'
  */

void left_rotate(char *str, int d) {
    size_t n = 0;
    while (str[n] != '\0') n++;
    if (n == 0) return;
    d = d % n;
    if (d == 0) return;

    char *temp = (char *)malloc(d + 1);
    if (temp == NULL) return;

    for (size_t i = 0; i < d; i++) {
        temp[i] = str[i];
    }
    temp[d] = '\0';
    /* Possible weaknesses found:
     *  call to undeclared library function 'memmove' with type 'void *(void *, const void *, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'memmove' [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'memmove'
     */
    memmove(str, str + d, n - d + 1);
    for (size_t i = n - d; i < n; i++) {
        str[i] = temp[i - (n - d)];
    }

    free(temp);
}

int main() {
    char str[] = "abcdef";
    int d = 2;
    left_rotate(str, d);
    printf("%s\n", str);
    return 0;
}