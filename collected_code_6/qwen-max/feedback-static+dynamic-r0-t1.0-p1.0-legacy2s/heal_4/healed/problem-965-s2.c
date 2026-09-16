#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(char *str) {
    if (str == NULL) return NULL;
    
    char *result = str;
    int i, j = 0;
    for (i = 0; str[i]; ++i) {
        if (isupper((unsigned char)str[i])) {
            if (i > 0 && (!isupper((unsigned char)str[i-1]) || i == strlen(str) - 1)) {
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
    char str[] = "ThisIsCamelCase";
    camel_to_snake(str);
    printf("Converted string: %s\n", str);

    char str2[] = "PythonLanguage";
    camel_to_snake(str2);
    printf("Converted string: %s\n", str2);

    char str3[] = "PythonProgram";
    camel_to_snake(str3);
    printf("Converted string: %s\n", str3);

    return 0;
}