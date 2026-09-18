#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_leading_zeroes(const char* ip) {
    if (ip == NULL) {
        return NULL;
    }

    char* result = malloc(strlen(ip) + 1);
    if (result == NULL) {
        return NULL;
    }

    const char* ptr = ip;
    char* res_ptr = result;
    int in_octet = 0;
    int zero_count = 0;

    while (*ptr != '\0') {
        if (*ptr == '.') {
            if (zero_count > 0 && !in_octet) {
                *res_ptr++ = '0';
            }
            *res_ptr++ = '.';
            in_octet = 0;
            zero_count = 0;
        } else if (*ptr == '0') {
            if (in_octet) {
                *res_ptr++ = '0';
            } else {
                zero_count++;
            }
        } else if (*ptr > '0' && *ptr <= '9') {
            *res_ptr++ = *ptr;
            in_octet = 1;
        } else {
            free(result);
            return NULL;
        }
        ptr++;
    }

    if (zero_count > 0 && !in_octet) {
        *res_ptr++ = '0';
    }

    *res_ptr = '\0';
    return result;
}

int main(void) {
    const char* ip1 = "192.168.001.001";
    const char* ip2 = "000.000.000.000";
    const char* ip3 = "010.00.02.0";
    const char* ip4 = "127.0.0.1";

    char* res1 = remove_leading_zeroes(ip1);
    char* res2 = remove_leading_zeroes(ip2);
    char* res3 = remove_leading_zeroes(ip3);
    char* res4 = remove_leading_zeroes(ip4);

    if (res1) {
        printf("%s -> %s\n", ip1, res1);
        free(res1);
    }
    if (res2) {
        printf("%s -> %s\n", ip2, res2);
        free(res2);
    }
    if (res3) {
        printf("%s -> %s\n", ip3, res3);
        free(res3);
    }
    if (res4) {
        printf("%s -> %s\n", ip4, res4);
        free(res4);
    }

    return 0;
}