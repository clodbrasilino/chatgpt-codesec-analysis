#define _POSIX_C_SOURCE 200809L

#include <stddef.h>
#include <ctype.h>
#include <stdio.h>

int remove_lowercase_substrings(char *str, size_t size)
{
    size_t read = 0, write = 0;

    if (str == NULL || size == 0) {
        return -1;
    }

    while (read < size && str[read] != '\0') {
        if (islower((unsigned char)str[read])) {
            while (read < size && str[read] != '\0' && islower((unsigned char)str[read])) {
                read++;
            }
        } else {
            if (write + 1 >= size) {
                return -1;
            }
            str[write++] = str[read++];
        }
    }

    if (write >= size) {
        return -1;
    }

    str[write] = '\0';
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