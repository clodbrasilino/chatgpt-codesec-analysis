#define _POSIX_C_SOURCE 200809L

#include <sys/types.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

int remove_lowercase_substrings(char *str) {
    regex_t regex;
    regmatch_t match;
    size_t read = 0;
    size_t write = 0;
    size_t len;
    int ret;

    if (str == NULL) {
        return -1;
    }

    ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    while (str[read] != '\0') {
        ret = regexec(&regex, str + read, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            len = strlen(str + read);
            memmove(str + write, str + read, len + 1);
            write += len;
            break;
        } else if (ret != 0) {
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo < match.rm_so) {
            regfree(&regex);
            return -1;
        }

        len = (size_t)match.rm_so;
        if (len > 0) {
            memmove(str + write, str + read, len);
            write += len;
        }

        if (match.rm_eo == match.rm_so) {
            str[write++] = str[read++];
            continue;
        }

        read += (size_t)match.rm_eo;
    }

    str[write] = '\0';
    regfree(&regex);
    return 0;
}

int main(void) {
    char text[] = "HelloWorld";

    if (remove_lowercase_substrings(text) == 0) {
        printf("%s\n", text);
    }

    return 0;
}