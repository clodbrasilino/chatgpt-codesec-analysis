#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_leading_zeroes(const char* ip) {
    if (ip == NULL) {
        return NULL;
    }

    size_t len = 0;
    
    while (len < 256 && ip[len] != '\0') {
        len++;
    }
    
    if (len == 256) {
        return NULL;
    }

    char* result = malloc(len + 1);
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
        } else if (*ptr >= '1' && *ptr <= '9') {
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
    const char* ip3 = "010.000.015.00";
    const char* ip4 = "127.0.0.1";

    char* res1 = remove_leading_zeroes(ip1);
    char* res2 = remove_leading_zeroes(ip2);
    char* res3 = remove_leading_zeroes(ip3);
    char* res4 = remove_leading_zeroes(ip4);

    if (res1) {
        printf("%s\n", res1);
        free(res1);
    }
    if (res2) {
        printf("%s\n", res2);
        free(res2);
    }
    if (res3) {
        printf("%s\n", res3);
        free(res3);
    }
    if (res4) {
        printf("%s\n", res4);
        free(res4);
    }

    return 0;
}