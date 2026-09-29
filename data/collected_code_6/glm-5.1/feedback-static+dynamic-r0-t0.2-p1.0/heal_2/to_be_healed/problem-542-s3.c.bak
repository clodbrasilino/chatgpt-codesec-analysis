#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* replace_with_colon(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;
    regmatch_t match;

    while (i < len) {
        ret = regexec(&regex, str + i, 1, &match, 0);
        if (ret == 0) {
            size_t start = i + match.rm_so;
            size_t end = i + match.rm_eo;

            memcpy(result + j, str + i, start - i);
            j += start - i;

            result[j++] = ':';

            i = end;
        } else {
            memcpy(result + j, str + i, len - i);
            j += len - i;
            i = len;
        }
    }

    result[j] = '\0';
    regfree(&regex);

    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char* res = replace_with_colon(argv[1]);
    if (res == NULL) {
        fprintf(stderr, "Error: Memory allocation or regex compilation failed\n");
        return 1;
    }

    printf("%s\n", res);
    free(res);

    return 0;
}