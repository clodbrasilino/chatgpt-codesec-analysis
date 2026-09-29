#include <stdio.h>
#include <stddef.h>

int remove_leading_zeroes(char *ip, size_t size) {
    if (ip == NULL || size == 0) {
        return -1;
    }

    size_t read = 0;
    size_t write = 0;
    int at_octet_start = 1;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (read < size && ip[read] != '\0') {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (ip[read] == '.') {
            if (write + 1 < size) {
                ip[write++] = '.';
            } else {
                break;
            }
            read++;
            at_octet_start = 1;
            continue;
        }

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (ip[read] < '0' || ip[read] > '9') {
            return -1;
        }

        if (at_octet_start) {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while (read < size && ip[read] == '0' &&
                   (read + 1 < size) &&
                   ip[read + 1] >= '0' && ip[read + 1] <= '9') {
                read++;
            }
            at_octet_start = 0;
        }

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (read >= size || ip[read] == '\0') {
            break;
        }

        if (write + 1 < size) {
            ip[write++] = ip[read++];
        } else {
            break;
        }
    }

    if (write < size) {
        ip[write] = '\0';
    } else if (size > 0) {
        ip[size - 1] = '\0';
    }

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