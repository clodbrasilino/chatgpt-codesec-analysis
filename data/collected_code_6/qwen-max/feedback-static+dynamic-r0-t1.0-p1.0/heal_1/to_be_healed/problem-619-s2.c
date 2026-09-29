#include <stdio.h>
#include <string.h>
#include <ctype.h>

void move_numbers(char *str) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[100] = "";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[100] = "";
    int j = 0, k = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (isdigit(str[i])) {
            result[j++] = str[i];
        } else {
            temp[k++] = str[i];
        }
    }

    while (k > 0) {
        temp[k--] = '\0';
    }

    /* Possible weaknesses found:
     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
     */
    strcat(result, temp);
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(str, result);
}

int main() {
    char str[] = "a2b3c4d5e6";
    move_numbers(str);
    printf("%s\n", str);
    return 0;
}