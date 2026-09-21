#include <stdio.h>
#include <string.h>

int remove_leading_zeroes(char *ip) {
    if (ip == NULL) return -1;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(ip);
    size_t write = 0, read = 0;
    int at_octet_start = 1;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (read < len) {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (ip[read] == '.') {
            ip[write++] = '.';
            read++;
            at_octet_start = 1;
            continue;
        }
        if (at_octet_start) {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while (read < len && ip[read] == '0' && read + 1 < len &&
                   ip[read + 1] >= '0' && ip[read + 1] <= '9') {
                read++;
            }
            at_octet_start = 0;
        }
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (read < len) {
            ip[write++] = ip[read++];
        }
    }
    ip[write] = '\0';
    return 0;
}

int main(void) {
    char ip[] = "192.168.001.001";
    if (remove_leading_zeroes(ip) != 0) return 1;
    printf("%s\n", ip);
    return 0;
}