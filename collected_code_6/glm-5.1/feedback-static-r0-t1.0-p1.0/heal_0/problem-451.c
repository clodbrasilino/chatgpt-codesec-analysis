#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* remove_whitespaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[[:space:]]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t length = strlen(str);
    char *result = malloc(length + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    regmatch_t match;
    size_t read_pos = 0;
    size_t write_pos = 0;

    while (read_pos < length) {
        ret = regexec(&regex, str + read_pos, 1, &match, 0);
        if (ret == 0 && match.rm_so == 0) {
            read_pos += match.rm_eo;
        } else {
            size_t end = (ret == 0) ? (size_t)match.rm_so : (length - read_pos);
            memmove(result + write_pos, str + read_pos, end);
            write_pos += end;
            read_pos += end;
            if (ret == 0) {
                read_pos += match.rm_eo - match.rm_so;
            }
        }
    }

    result[write_pos] = '\0';
    regfree(&regex);

    char *shrunk = realloc(result, write_pos + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    char *result = remove_whitespaces("  H e l l o \t W o r l d \n ");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }
    return 0;
}