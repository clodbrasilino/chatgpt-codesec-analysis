#include <stdio.h>
#include <stddef.h>

int remove_leading_zeroes(char *ip, size_t size) {
    if (ip == NULL || size == 0) {
        return -1;
    }

    char *read = ip;
    char *write = ip;
    int at_octet_start = 1;
    const char *end = ip + size - 1;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (*read != '\0' && read < end) {
        if (*read == '.') {
            if (write < end) {
                *write++ = '.';
            }
            read++;
            at_octet_start = 1;
            continue;
        }

        if (at_octet_start) {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while (read < end && *read == '0' && read[1] >= '0' && read[1] <= '9') {
                read++;
            }
            at_octet_start = 0;
        }

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (*read == '\0' || read >= end) {
            break;
        }

        if (write < end) {
            *write++ = *read++;
        } else {
            break;
        }
    }

    *write = '\0';
    return 0;
}

int main(void) {
    char ip[] = "192.168.001.001";

    if (remove_leading_zeroes(ip, sizeof(ip)) != 0) {
        return 1;
    }

    printf("%s\n", ip);

    return 0;
}