#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'GoogleDart', got <no output>
  *  test case 0 failed: expected 'GoogleFlutter', got <no output>
  *  test case 2 failed: expected 'iOSSwift', got <no output>
  */

char *remove_whitespaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t res_idx = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r' && str[i] != '\f' && str[i] != '\v') {
            result[res_idx++] = str[i];
        }
    }

    result[res_idx] = '\0';
    return result;
}

int main(void) {
    const char *input = " Hello \t World \n from C \r ";
    char *output = remove_whitespaces(input);
    
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    
    return 0;
}