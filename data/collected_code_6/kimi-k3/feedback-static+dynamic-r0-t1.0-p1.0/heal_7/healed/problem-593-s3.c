#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void removeLeadingZeros(char *ip, size_t ip_size) {
    if (ip == NULL || *ip == '\0' || ip_size == 0) {
        return;
    }

    char result[16] = {0};
    char *token;
    char *rest = ip;
    int first = 1;
    size_t result_len = 0;

    while ((token = strtok_r(rest, ".", &rest)) != NULL) {
        while (*token == '0' && *(token + 1) != '\0') {
            token++;
        }

        size_t token_len = strnlen(token, 4);
        size_t needed = first ? token_len : token_len + 1;

        if (result_len + needed >= sizeof(result)) {
            break;
        }

        if (!first) {
            result[result_len++] = '.';
        }

        if (token_len > 0) {
            size_t remaining = sizeof(result) - result_len - 1;
            if (token_len <= remaining) {
                memcpy(result + result_len, token, token_len);
                result_len += token_len;
            }
        }
        result[result_len] = '\0';
        first = 0;
    }

    if (result_len > 0) {
        size_t ip_len = strnlen(ip, ip_size - 1);
        if (result_len <= ip_len && result_len < ip_size) {
            size_t copy_len = (result_len < ip_len) ? result_len : ip_len;
            if (copy_len < ip_size) {
                memcpy(ip, result, copy_len);
                ip[copy_len] = '\0';
            }
        }
    }
}

int main() {
    char ip1[16] = "192.168.001.001";
    char ip2[16] = "010.000.000.001";
    char ip3[16] = "000.000.000.000";
    char ip4[16] = "255.255.255.255";

    printf("Original: %s\n", ip1);
    removeLeadingZeros(ip1, sizeof(ip1));
    printf("Modified: %s\n\n", ip1);

    printf("Original: %s\n", ip2);
    removeLeadingZeros(ip2, sizeof(ip2));
    printf("Modified: %s\n\n", ip2);

    printf("Original: %s\n", ip3);
    removeLeadingZeros(ip3, sizeof(ip3));
    printf("Modified: %s\n\n", ip3);

    printf("Original: %s\n", ip4);
    removeLeadingZeros(ip4, sizeof(ip4));
    printf("Modified: %s\n", ip4);

    return 0;
}