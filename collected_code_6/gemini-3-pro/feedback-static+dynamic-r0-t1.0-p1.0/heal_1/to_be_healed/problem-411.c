#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'GooglePixel', got googlePixel
  *  test case 0 failed: expected 'AndroidTv', got androidTv
  *  test case 2 failed: expected 'AppleWatch', got appleWatch
  */

char* snake_to_camel(const char* snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "_[a-z]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t len = strlen(snake_str);
    char* camel_str = (char*)malloc(len + 1);
    if (camel_str == NULL) {
        regfree(&regex);
        return NULL;
    }

    regmatch_t pmatch[1];
    const char* cursor = snake_str;
    char* dest = camel_str;

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        size_t prefix_len = pmatch[0].rm_so;
        strncpy(dest, cursor, prefix_len);
        dest += prefix_len;
        
        *dest = toupper((unsigned char)cursor[pmatch[0].rm_so + 1]);
        dest++;
        
        cursor += pmatch[0].rm_eo;
    }

    strcpy(dest, cursor);
    regfree(&regex);

    return camel_str;
}

int main(void) {
    const char* snake = "this_is_a_snake_case_string";
    char* camel = snake_to_camel(snake);

    if (camel != NULL) {
        printf("%s\n", camel);
        free(camel);
    } else {
        fprintf(stderr, "Error converting string.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}