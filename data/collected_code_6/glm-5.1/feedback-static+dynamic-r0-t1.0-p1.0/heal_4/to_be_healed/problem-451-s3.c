#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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
        if (!isspace((unsigned char)str[i])) {
            result[res_idx++] = str[i];
        }
    }

    result[res_idx] = '\0';
    return result;
}

int main(void) {
    const char *inputs[] = {
        "Google Flutter",
        "Google Dart",
        "iOS Swift"
    };
    
    for (size_t i = 0; i < sizeof(inputs) / sizeof(inputs[0]); i++) {
        char *output = remove_whitespaces(inputs[i]);
        if (output != NULL) {
            printf("%s\n", output);
            free(output);
        }
    }
    
    return 0;
}