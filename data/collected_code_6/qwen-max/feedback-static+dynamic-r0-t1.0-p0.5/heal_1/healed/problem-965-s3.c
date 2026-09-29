#include <stdio.h>
#include <ctype.h>
#include <string.h>

char *camel_to_snake(const char *str, char *result, size_t result_size) {
    int i, j = 0;
    for (i = 0; str[i] && j < result_size - 1; ++i) {
        if (isupper((unsigned char)str[i])) {
            if (i > 0 && str[i-1] != ' ') {
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
    char output[100];
    camel_to_snake(input, output, sizeof(output));
    printf("%s\n", output);
    return 0;
}