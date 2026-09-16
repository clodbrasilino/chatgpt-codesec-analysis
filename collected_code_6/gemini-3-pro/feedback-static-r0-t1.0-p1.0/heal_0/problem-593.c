#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* remove_leading_zeroes(const char* ip) {
    if (ip == NULL) {
        return NULL;
    }

    size_t len = strlen(ip);
    if (len == 0 || len > 39) {
        return NULL;
    }

    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0, j = 0;
    while (ip[i] != '\0') {
        int zero_count = 0;
        int num_start = i;

        while (ip[i] >= '0' && ip[i] <= '9') {
            if (ip[i] == '0' && i == (size_t)num_start && ip[i+1] != '.' && ip[i+1] != '\0') {
                zero_count++;
                num_start++;
            }
            i++;
        }

        int k = num_start;
        while (k < (int)i) {
            result[j++] = ip[k++];
        }

        if (ip[i] != '\0') {
            result[j++] = ip[i++];
        }
    }

    result[j] = '\0';
    return result;
}

int main(void) {
    const char* ip1 = "192.168.01.001";
    char* res1 = remove_leading_zeroes(ip1);
    if (res1 != NULL) {
        printf("%s\n", res1);
        free(res1);
    }

    const char* ip2 = "000.000.000.000";
    char* res2 = remove_leading_zeroes(ip2);
    if (res2 != NULL) {
        printf("%s\n", res2);
        free(res2);
    }

    const char* ip3 = "010.0.0.01";
    char* res3 = remove_leading_zeroes(ip3);
    if (res3 != NULL) {
        printf("%s\n", res3);
        free(res3);
    }

    return 0;
}