#define _POSIX_C_SOURCE 200809L

#include <sys/types.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

int remove_lowercase_substrings(char *str, size_t size) {
    regex_t regex;
    regmatch_t match;
    size_t read = 0;
    size_t write = 0;
    size_t len_orig;
    int ret;

    if (str == NULL || size == 0) {
        return -1;
    }

    len_orig = strnlen(str, size);
    if (len_orig == size) {
        return -1;
    }

    ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    while (read < len_orig) {
        ret = regexec(&regex, str + read, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remain = len_orig - read;
            if (remain >= size - write) {
                regfree(&regex);
                return -1;
            }
            memmove(str + write, str + read, remain);
            write += remain;
            str[write] = '\0';
            break;
        } else if (ret != 0) {
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo < match.rm_so) {
            regfree(&regex);
            return -1;
        }

        if (match.rm_eo == 0) {
            if (1 >= size - write) {
                regfree(&regex);
                return -1;
            }
            str[write] = str[read];
            write++;
            read++;
            continue;
        }

        {
            size_t prefix_len = (size_t)match.rm_so;
            if (prefix_len > 0) {
                if (prefix_len >= size - write) {
                    regfree(&regex);
                    return -1;
                }
                memmove(str + write, str + read, prefix_len);
                write += prefix_len;
            }
            read += (size_t)match.rm_eo;
        }
    }

    if (read == len_orig) {
        if (write < size) {
            str[write] = '\0';
        } else {
            regfree(&regex);
            return -1;
        }
    }

    regfree(&regex);
    return 0;
}

int main(void) {
    char buffer[128] = "HelloWorld123abcXYZ lowerCASE";
    printf("Before: %s\n", buffer);
    if (remove_lowercase_substrings(buffer, sizeof(buffer)) == 0) {
        printf("After: %s\n", buffer);
    } else {
        printf("Error processing string\n");
    }
    return 0;
}