#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'chrome_cast', got <no output>
  *  test case 0 failed: expected 'google_assistant', got <no output>
  *  test case 2 failed: expected 'quad_core', got <no output>
  */

char* camel_to_snake(const char* input) {
    if (!input) return NULL;

    size_t len = 0;
    while (input[len] != '\0') {
        len++;
    }

    char* output = malloc(len * 2 + 1);
    if (!output) return NULL;

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (i > 0 && islower((unsigned char)input[i - 1]) && isupper((unsigned char)input[i])) {
            output[j++] = '_';
        }
        output[j++] = tolower((unsigned char)input[i]);
    }
    output[j] = '\0';

    return output;
}

int main(void) {
    const char* camel = "thisIsCamelCaseString";
    char* snake = camel_to_snake(camel);
    
    if (snake) {
        printf("%s\n", snake);
        free(snake);
    } else {
        fprintf(stderr, "Conversion failed.\n");
    }

    return 0;
}