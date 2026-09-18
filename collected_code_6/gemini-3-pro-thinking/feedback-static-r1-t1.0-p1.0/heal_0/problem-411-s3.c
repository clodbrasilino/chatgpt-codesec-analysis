#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char *snake_to_camel(const char *snake_case) {
    if (snake_case == NULL) {
        return NULL;
    }

    regex_t regex;
    int reti = regcomp(&regex, "_([a-z])", REG_EXTENDED);
    if (reti != 0) {
        return NULL;
    }

    size_t len = strlen(snake_case);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    char *dest = result;
    const char *src = snake_case;
    regmatch_t pmatch[2];

    while (1) {
        reti = regexec(&regex, src, 2, pmatch, 0);
        
        if (reti == REG_NOMATCH) {
            strcpy(dest, src);
            break;
        }
        
        if (reti != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        size_t prefix_len = pmatch[0].rm_so;
        memcpy(dest, src, prefix_len);
        dest += prefix_len;

        *dest++ = toupper((unsigned char)src[pmatch[1].rm_so]);

        src += pmatch[0].rm_eo;
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *snake_str = "this_is_a_snake_case_string";
    
    char *camel_str = snake_to_camel(snake_str);
    
    if (camel_str != NULL) {
        printf("%s\n", camel_str);
        free(camel_str);
    } else {
        fprintf(stderr, "Error during conversion\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}