#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

char* snake_to_camel(const char *input) {
    regex_t re;
    regmatch_t match[2];
    const char *p = input;
    char *output, *q;
    int len;

    if (regcomp(&re, "(_[a-z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        return NULL;
    }

    len = strlen(input);
    output = malloc(len + 1);
    if (!output) {
        return NULL;
    }
    q = output;

    while (*p) {
        if (regexec(&re, p, 2, match, 0) == 0 && match[1].rm_so == 0) {
            *q++ = toupper(p[1]);
            p += 2;  // Skip the underscore and the following character
        } else {
            *q++ = *p++;
        }
    }
    *q = '\0';

    regfree(&re);
    return output;
}

int main() {
    const char *input = "this_is_a_snake_case_string";
    char *output = snake_to_camel(input);

    if (output) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Error converting string.\n");
    }

    return 0;
}