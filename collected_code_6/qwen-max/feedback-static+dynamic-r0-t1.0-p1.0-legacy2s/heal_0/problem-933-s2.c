#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *camel_to_snake(const char *str) {
    const int buffer_size = 256;
    char *snake_case = (char *)malloc(buffer_size * sizeof(char));
    if (!snake_case) {
        return NULL;
    }

    memset(snake_case, 0, buffer_size);

    regex_t regex;
    regmatch_t matches[3];
    if (regcomp(&regex, "([a-z0-9])([A-Z])|([A-Z])([A-Z][a-z])", REG_EXTENDED)) {
        free(snake_case);
        return NULL;
    }

    int pos = 0;
    int match_pos = 0;
    while (regexec(&regex, str + pos, 3, matches, 0) == 0) {
        int match_start = matches[0].rm_so;
        int match_end = matches[0].rm_eo;
        strncpy(snake_case + match_pos, str + pos, match_start);
        match_pos += match_start;

        if (matches[1].rm_so != -1 && matches[2].rm_so != -1) {
            snake_case[match_pos++] = '_';
            snake_case[match_pos++] = tolower(str[pos + match_start]);
        } else if (matches[3].rm_so != -1 && matches[4].rm_so != -1) {
            snake_case[match_pos++] = '_';
            snake_case[match_pos++] = tolower(str[pos + match_start]);
        }

        pos += match_end;
    }

    strcpy(snake_case + match_pos, str + pos);
    regfree(&regex);

    return snake_case;
}

int main() {
    const char *camel_case = "ThisIsCamelCaseString";
    char *snake_case = camel_to_snake(camel_case);
    if (snake_case) {
        printf("%s\n", snake_case);
        free(snake_case);
    } else {
        printf("Conversion failed.\n");
    }
    return 0;
}