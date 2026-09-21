#define _POSIX_C_SOURCE 200809L

#include <stddef.h>
#include <ctype.h>
#include <stdio.h>

int remove_lowercase_substrings(char *str, size_t size)
{
    const char *src = str;
    char *dst = str;
    const char *const end = str + size;

    if (str == NULL || size == 0) {
        return -1;
    }

    while (src < end && *src != '\0') {
        if (islower((unsigned char)*src)) {
            while (src < end && *src != '\0' && islower((unsigned char)*src)) {
                src++;
            }
        } else {
            if (dst + 1 >= end) {
                return -1;
            }
            *dst++ = *src++;
        }
    }

    if (dst >= end) {
        return -1;
    }

    *dst = '\0';
    return 0;
}

int main(void)
{
    char buffer[] = "HelloWorld123abcXYZ def __lower__";

    if (remove_lowercase_substrings(buffer, sizeof(buffer)) == 0) {
        printf("result: '%s'\n", buffer);
    } else {
        printf("error\n");
    }

    return 0;
}