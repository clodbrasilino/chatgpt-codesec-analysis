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

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (read < size && str[read] != '\0') {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (islower((unsigned char)str[read])) {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while (read < size && str[read] != '\0' && islower((unsigned char)str[read])) {
                read++;
            }
        } else {
            if (write + 1 >= size) {
                return -1;
            }
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            str[write] = str[read];
            write++;
            read++;
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[100] = "HelloWorld123abcXYZ def __lower__";

    if (remove_lowercase_substrings(buffer, sizeof(buffer)) == 0) {
        printf("result: '%s'\n", buffer);
    } else {
        printf("error\n");
    }

    return 0;
}