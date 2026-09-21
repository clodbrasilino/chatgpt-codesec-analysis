#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'chrome_cast', got <no output>
  *  test case 0 failed: expected 'google_assistant', got <no output>
  *  test case 2 failed: expected 'quad_core', got <no output>
  */

char* camel_to_snake(const char *input) {
    if (!input) return NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t in_len = strlen(input);
    size_t out_size = in_len * 2 + 1;
    char *result = (char*)malloc(out_size);
    if (!result) return NULL;

    size_t j = 0;
    for (size_t i = 0; i < in_len; i++) {
        char c = input[i];
        if (isupper((unsigned char)c)) {
            if (i > 0) {
                result[j++] = '_';
            }
            result[j++] = tolower((unsigned char)c);
        } else {
            result[j++] = c;
        }
    }
    result[j] = '\0';

    char *final_result = (char*)realloc(result, j + 1);
    return final_result ? final_result : result;
}

int main(void) {
    const char *test_str = "camelCaseStringExample";
    char *snake_str = camel_to_snake(test_str);
    
    if (snake_str) {
        printf("%s\n", snake_str);
        free(snake_str);
    }
    
    return 0;
}