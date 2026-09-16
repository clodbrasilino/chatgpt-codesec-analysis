#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'quad_core', got Quad_core
  *  test case 1 failed: expected 'chrome_cast', got Chrome_cast
  *  test case 0 failed: expected 'google_assistant', got Google_assistant
  */

char* camel_to_snake(const char *input) {
    if (!input) return NULL;

    regex_t regex;
    int ret = regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t out_size = strlen(input) * 2 + 1;
    char *result = (char*)malloc(out_size);
    if (!result) {
        regfree(&regex);
        return NULL;
    }

    const char *p = input;
    char *q = result;
    regmatch_t pmatch[3];

    while (regexec(&regex, p, 3, pmatch, 0) == 0) {
        size_t len = pmatch[1].rm_eo;
        memcpy(q, p, len);
        q += len;
        
        *q++ = '_';
        *q++ = p[pmatch[2].rm_so] + 32;
        
        p += pmatch[2].rm_eo;
    }

    strcpy(q, p);
    regfree(&regex);

    char *final_result = (char*)realloc(result, strlen(result) + 1);
    if (!final_result) {
        return result; 
    }
    
    return final_result;
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