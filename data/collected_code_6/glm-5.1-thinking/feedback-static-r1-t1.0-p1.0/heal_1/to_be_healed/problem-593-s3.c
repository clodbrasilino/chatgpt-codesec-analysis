#include <stdio.h>
#include <string.h>
#include <ctype.h>

int remove_ip_leading_zeroes(const char *src, char *dest, size_t dest_size) {
    /* Possible weaknesses found:
     *  Assuming that condition 'dest_size==0' is not redundant
     */
    if (src == NULL || dest == NULL || dest_size == 0) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t src_len = strlen(src);
    if (src_len == 0) {
        /* Possible weaknesses found:
         *  Condition 'dest_size>=1' is always true [knownConditionTrueFalse]
         *  Condition 'dest_size>=1' is always true
         */
        if (dest_size >= 1) {
            dest[0] = '\0';
            return 0;
        }
        return -1;
    }

    size_t j = 0;
    for (size_t i = 0; i < src_len; ++i) {
        if (src[i] == '0' && isdigit((unsigned char)src[i + 1]) && (i == 0 || src[i - 1] == '.')) {
            continue;
        }
        if (j >= dest_size - 1) {
            break;
        }
        dest[j++] = src[i];
    }

    dest[j] = '\0';
    return (j < src_len) ? -1 : 0;
}

int main(void) {
    const char *addresses[] = {
        "192.168.001.010",
        "010.000.000.001",
        "0.0.0.0",
        "255.255.255.255",
        "001.002.003.004"
    };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[16];
    size_t count = sizeof(addresses) / sizeof(addresses[0]);

    for (size_t i = 0; i < count; ++i) {
        if (remove_ip_leading_zeroes(addresses[i], buffer, sizeof(buffer)) == 0) {
            printf("%s -> %s\n", addresses[i], buffer);
        } else {
            printf("Error processing: %s\n", addresses[i]);
        }
    }

    return 0;
}