#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* minimize_string_length(char *str, char ch) {
    int len = strlen(str);
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ch) {
            count++;
        }
    }
    if (count == 0) {
        return str;
    }
    char *result = (char*)malloc((len - count + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ch) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    free(str);
    return result;
}

int main() {
    char str[] = "example string with some characters to remove";
    char ch = 'e';
    char *minimized_str = minimize_string_length(str, ch);
    if (minimized_str != NULL) {
        printf("Minimized string: %s\n", minimized_str);
        free(minimized_str);
    } else {
        printf("Error in minimizing the string.\n");
    }
    return 0;
}