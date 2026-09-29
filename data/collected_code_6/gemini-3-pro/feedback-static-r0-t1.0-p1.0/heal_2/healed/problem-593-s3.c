#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* remove_leading_zeroes(const char* ip) {
    if (ip == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (len <= 15 && ip[len] != '\0') {
        len++;
    }
    
    if (len == 0 || len > 15) {
        return NULL;
    }

    char* result = (char*)malloc(16);
    if (result == NULL) {
        return NULL;
    }

    const char* ptr = ip;
    char* res_ptr = result;
    
    int val = 0;
    int digits = 0;
    int dot_count = 0;

    while (*ptr != '\0') {
        if (*ptr == '.') {
            if (digits == 0 || val > 255) {
                free(result);
                return NULL;
            }
            
            size_t rem = (size_t)(result + 16 - res_ptr);
            int written = snprintf(res_ptr, rem, "%d.", val);
            if (written < 0 || (size_t)written >= rem) {
                free(result);
                return NULL;
            }
            
            res_ptr += written;
            val = 0;
            digits = 0;
            dot_count++;
        } else if (*ptr >= '0' && *ptr <= '9') {
            if (digits < 3) {
                val = val * 10 + (*ptr - '0');
                digits++;
            } else {
                free(result);
                return NULL;
            }
        } else {
            free(result);
            return NULL;
        }
        ptr++;
    }

    if (digits == 0 || val > 255 || dot_count != 3) {
        free(result);
        return NULL;
    }
    
    size_t rem = (size_t)(result + 16 - res_ptr);
    snprintf(res_ptr, rem, "%d", val);

    return result;
}

int main(void) {
    const char* ip1 = "192.168.001.001";
    char* clean_ip1 = remove_leading_zeroes(ip1);
    if (clean_ip1 != NULL) {
        printf("%s\n", clean_ip1);
        free(clean_ip1);
    }

    const char* ip2 = "010.000.025.105";
    char* clean_ip2 = remove_leading_zeroes(ip2);
    if (clean_ip2 != NULL) {
        printf("%s\n", clean_ip2);
        free(clean_ip2);
    }

    return 0;
}