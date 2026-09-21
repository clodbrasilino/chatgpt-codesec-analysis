#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void removeLeadingZeros(char *ip) {
    if (ip == NULL || *ip == '\0') {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[16];
    size_t result_len = 0;
    char *token;
    char *rest = ip;
    int first = 1;

    while ((token = strtok_r(rest, ".", &rest)) != NULL) {
        while (*token == '0' && *(token + 1) != '\0') {
            token++;
        }

        size_t token_len = strnlen(token, 4);
        if (token_len > 3) {
            return;
        }

        size_t needed = token_len + (first ? 0 : 1);

        if (result_len + needed >= sizeof(result)) {
            return;
        }

        if (!first) {
            result[result_len++] = '.';
        }

        if (token_len > 0) {
            if (result_len + token_len >= sizeof(result)) {
                return;
            }
            if (result_len + token_len < sizeof(result)) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_len, token, token_len);
                result_len += token_len;
            }
        }
        first = 0;
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'result_len<sizeof(result)' is not redundant
     */
    if (result_len > 0 && result_len < sizeof(result)) {
        result[result_len] = '\0';
        size_t ip_len = strnlen(ip, 16);
        /* Possible weaknesses found:
         *  Condition 'result_len+1<=16' is always true
         *  Condition 'result_len+1<=16' is always true [knownConditionTrueFalse]
         *  outer condition: result_len+1<=ip_len+1
         */
        if (result_len + 1 <= ip_len + 1 && result_len + 1 <= 16) {
            /* Possible weaknesses found:
             *  identical inner condition: result_len+1<=ip_len+1
             *  Identical inner 'if' condition is always true. [identicalInnerCondition]
             */
            if (result_len + 1 <= ip_len + 1) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(ip, result, result_len + 1);
            }
        }
    }
}

int main(void) {
    char ip1[] = "192.168.001.001";
    char ip2[] = "010.000.000.001";
    char ip3[] = "000.000.000.000";
    char ip4[] = "255.255.255.255";

    printf("Original: %s\n", ip1);
    removeLeadingZeros(ip1);
    printf("Modified: %s\n\n", ip1);

    printf("Original: %s\n", ip2);
    removeLeadingZeros(ip2);
    printf("Modified: %s\n\n", ip2);

    printf("Original: %s\n", ip3);
    removeLeadingZeros(ip3);
    printf("Modified: %s\n\n", ip3);

    printf("Original: %s\n", ip4);
    removeLeadingZeros(ip4);
    printf("Modified: %s\n", ip4);

    return 0;
}