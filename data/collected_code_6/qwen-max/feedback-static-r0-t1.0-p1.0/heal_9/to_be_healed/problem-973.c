#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void left_rotate(char *str, size_t len, int d) {
    d = (d % (int)len + len) % len;
    if (d == 0) return;

    char *temp = (char *)malloc(d + 1);
    if (temp == NULL) return;

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, str, d);
    temp[d] = '\0';

    memmove(str, str + d, len - d + 1);
    /* Possible weaknesses found:
     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
     */
    strcat(str, temp);

    free(temp);
}

int main() {
    char str[] = "abcdef";
    int d = 2;
    left_rotate(str, sizeof(str) / sizeof(str[0]) - 1, d);
    printf("%s\n", str);
    return 0;
}