#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* camel_to_snake(char *str) {
    char *p = str;
    static char result[100];
    int i = 0;

    if (str == NULL) return NULL;

    while (*p) {
        if (isupper((unsigned char)*p)) {
            if (i > 0 && result[i-1] != '_') {
                result[i++] = '_';
            }
            result[i++] = tolower((unsigned char)*p);
        } else {
            result[i++] = *p;
        }
        p++;
    }
    result[i] = '\0';
    return result;
}

int main() {
    char input[] = "ThisIsCamelCase";
    char *output = camel_to_snake(input);
    printf("%s\n", output);
    return 0;
}