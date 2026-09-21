#include <stdio.h>

int remove_leading_zeroes(char *ip) {
    if (ip == NULL) {
        return -1;
    }

    char *read = ip;
    char *write = ip;
    int at_octet_start = 1;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (*read != '\0') {
        if (*read == '.') {
            *write++ = '.';
            read++;
            at_octet_start = 1;
            continue;
        }

        if (at_octet_start) {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while (*read == '0' && read[1] >= '0' && read[1] <= '9') {
                read++;
            }
            at_octet_start = 0;
        }

        if (*read == '\0') {
            break;
        }

        *write++ = *read++;
    }

    *write = '\0';
    return 0;
}

int main(void) {
    char ip[] = "192.168.001.001";

    if (remove_leading_zeroes(ip) != 0) {
        return 1;
    }

    printf("%s\n", ip);

    return 0;
}