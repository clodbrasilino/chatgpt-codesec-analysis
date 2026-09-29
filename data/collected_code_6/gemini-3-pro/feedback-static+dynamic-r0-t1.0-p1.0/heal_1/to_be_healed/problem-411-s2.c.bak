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
    int reti;
    const char* pattern = "_([a-z])";
    size_t nmatch = 2;
    regmatch_t pmatch[2];

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        return NULL;
    }

    size_t len = strlen(snake_str);
    char* camel_str = (char*)malloc(len + 1);
    if (camel_str == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char* cursor = snake_str;
    char* dest = camel_str;

    while (regexec(&regex, cursor, nmatch, pmatch, 0) == 0) {
        size_t prefix_len = pmatch[0].rm_so;
        strncpy(dest, cursor, prefix_len);
        dest += prefix_len;

        *dest = toupper((unsigned char)cursor[pmatch[1].rm_so]);
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
        printf("Snake: %s\n", snake);
        printf("Camel: %s\n", camel);
        free(camel);
    } else {
        printf("Conversion failed or memory allocation error.\n");
    }

    return 0;
}