#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int insert_spaces(char *str) {
    regex_t regex;
    regmatch_t matches[2];
    size_t len = strnlen(str, 1024);
    char *modified_str = malloc((len * 2 + 1) * sizeof(char));
    if (modified_str == NULL) {
        return -1;
    }
    memcpy(modified_str, str, len);
    modified_str[len] = '\0';
    int offset = 0;

    if (regcomp(&regex, "([A-Z][^A-Z]*)", REG_EXTENDED) != 0) {
        free(modified_str);
        return -1;
    }

    while (regexec(&regex, modified_str + offset, 2, matches, 0) == 0) {
        if (matches[0].rm_so > 0 && modified_str[offset + matches[0].rm_so - 1] != ' ') {
            memmove(modified_str + offset + matches[0].rm_so + 1, modified_str + offset + matches[0].rm_so, len - (offset + matches[0].rm_so) + 1);
            modified_str[offset + matches[0].rm_so] = ' ';
            offset += 1;
        }
        offset += matches[0].rm_eo;
    }

    regfree(&regex);
    snprintf(str, 1024, "%s", modified_str);
    free(modified_str);
    return 0;
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    if (insert_spaces(str) == 0) {
        printf("%s\n", str);
    } else {
        printf("Error occurred.\n");
    }
    return 0;
}