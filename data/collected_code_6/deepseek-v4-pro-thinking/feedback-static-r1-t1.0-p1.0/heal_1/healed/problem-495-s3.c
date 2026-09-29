#define _POSIX_C_SOURCE 200809L

#include <sys/types.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

int remove_lowercase_substrings(char *str, size_t size)
{
    regex_t regex;
    regmatch_t match;
    size_t read = 0;
    size_t write = 0;
    size_t len;
    int ret;

    if (str == NULL || size == 0) {
        return -1;
    }

    ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    while (read < size && str[read] != '\0') {
        ret = regexec(&regex, str + read, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = size - read;
            len = strnlen(str + read, remaining);
            if (write + len >= size) {
                regfree(&regex);
                return -1;
            }
            memmove(str + write, str + read, len);
            write += len;
            if (write < size) {
                str[write] = '\0';
            }
            break;
        } else if (ret != 0) {
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo < match.rm_so) {
            regfree(&regex);
            return -1;
        }

        if ((size_t)match.rm_so > (size_t)(size - read)) {
            regfree(&regex);
            return -1;
        }

        len = (size_t)match.rm_so;
        if (len > 0) {
            if (write + len >= size) {
                regfree(&regex);
                return -1;
            }
            memmove(str + write, str + read, len);
            write += len;
        }

        if (match.rm_eo == match.rm_so) {
            if (write >= size || read >= size) {
                regfree(&regex);
                return -1;
            }
            str[write++] = str[read++];
            continue;
        }

        if ((size_t)match.rm_eo > (size_t)(size - read)) {
            regfree(&regex);
            return -1;
        }
        read += (size_t)match.rm_eo;
    }

    if (write < size) {
        str[write] = '\0';
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    char buffer[100] = "HelloWorld123abcXYZ def __lower__";

    if (remove_lowercase_substrings(buffer, sizeof(buffer)) == 0) {
        printf("result: '%s'\n", buffer);
    } else {
        printf("error\n");
    }

    return 0;
}