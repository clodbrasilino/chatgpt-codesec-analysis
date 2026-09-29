#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_leading_zeroes_ip(const char *ip) {
    size_t len = strlen(ip);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t res_idx = 0;
    size_t i = 0;

    while (ip[i] != '\0') {
        if (ip[i] == '0' && (i == 0 || ip[i - 1] == '.')) {
            if (ip[i + 1] != '\0' && ip[i + 1] != '.') {
                i++;
            } else {
                result[res_idx++] = ip[i++];
            }
        } else {
            result[res_idx++] = ip[i++];
        }
    }

    result[res_idx] = '\0';
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <ip_address>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *cleaned_ip = remove_leading_zeroes_ip(argv[1]);
    if (cleaned_ip == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", cleaned_ip);
    free(cleaned_ip);
    cleaned_ip = NULL;

    return EXIT_SUCCESS;
}