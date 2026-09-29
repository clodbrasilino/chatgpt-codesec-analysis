#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>
#include <ctype.h>

char *convert_snake_to_camel(const char *snake_str) {
    regex_t re;
    regmatch_t matches[2];
    const size_t buffer_size = 4096;
    char *camel_case = (char *)malloc(buffer_size);
    if (camel_case == NULL) return NULL;
    memset(camel_case, 0, buffer_size);

    if (regcomp(&re, "(_[a-z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        free(camel_case);
        return NULL;
    }

    char *result = camel_case;
    const char *p = snake_str;
    while (*p) {
        int match_count = regexec(&re, p, 2, matches, 0);
        if (match_count == 0) {
            if (matches[1].rm_so == 0) {
                *result++ = toupper((unsigned char)p[1]);
                p += 2;
            } else {
                *result++ = *p++;
            }
        } else {
            *result++ = *p++;
        }
    }

    *result = '\0';
    regfree(&re);
    return camel_case;
}

int main() {
    const char *input = "this_is_a_snake_case_string";
    char *output = convert_snake_to_camel(input);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    return 0;
}