#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* remove_leading_zeroes(const char* ip) {
    if (ip == NULL) {
        return NULL;
    }

    size_t len = strlen(ip);
    if (len == 0 || len > 15) {
        return NULL;
    }

    char* result = (char*)malloc(16 * sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    int res_idx = 0;
    int i = 0;
    int octet_start = 1;
    int zero_count = 0;

    while (ip[i] != '\0') {
        if (ip[i] == '.') {
            if (octet_start && zero_count > 0) {
                result[res_idx++] = '0';
            }
            result[res_idx++] = '.';
            octet_start = 1;
            zero_count = 0;
        } else if (isdigit((unsigned char)ip[i])) {
            if (octet_start && ip[i] == '0') {
                zero_count++;
            } else {
                octet_start = 0;
                result[res_idx++] = ip[i];
            }
        } else {
            free(result);
            return NULL;
        }
        i++;
    }

    if (octet_start && zero_count > 0) {
        result[res_idx++] = '0';
    }

    result[res_idx] = '\0';
    return result;
}

int main(void) {
    const char* test_ips[] = {
        "192.168.001.001",
        "010.000.000.000",
        "000.000.000.000",
        "127.0.0.1",
        "001.002.003.004",
        "255.255.255.255",
        "invalid.ip.address",
        NULL
    };

    for (int i = 0; test_ips[i] != NULL; i++) {
        char* cleaned_ip = remove_leading_zeroes(test_ips[i]);
        if (cleaned_ip != NULL) {
            printf("%s -> %s\n", test_ips[i], cleaned_ip);
            free(cleaned_ip);
        } else {
            printf("%s -> Invalid IP\n", test_ips[i]);
        }
    }

    return 0;
}