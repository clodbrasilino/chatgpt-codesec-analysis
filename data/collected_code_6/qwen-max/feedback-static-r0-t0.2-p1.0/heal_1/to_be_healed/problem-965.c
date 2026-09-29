#include <stdio.h>
#include <ctype.h>
#include <string.h>

char* camel_to_snake(char *str) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    static char result[100];
    int i, j = 0;
    for (i = 0; str[i]; ++i) {
        if (isupper((unsigned char)str[i])) {
            if (i > 0 && str[i-1] != '_') {
                result[j++] = '_';
            }
            result[j++] = tolower((unsigned char)str[i]);
        } else {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    return result;
}

int main() {
    char input[] = "ThisIsCamelCase";
    char *output = camel_to_snake(input);
    printf("%s\n", output);
    return 0;
}