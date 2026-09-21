#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void remove_odd_chars(char *str, size_t max_size) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[max_size];
    const char *read = str;
    char *write = result;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    for (size_t i = 0; i < max_size - 1 && read[i] != '\0'; i++) {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if ((read[i] >= '0' && read[i] <= '9' && (read[i] - '0') % 2 == 0) || (read[i] < '0' || read[i] > '9')) {
            if (write - result < max_size - 2) {
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                *write++ = read[i];
            }
        }
    }
    *write = '\0';

    size_t result_len = strnlen(result, max_size);
    if (result_len < max_size) {
        memmove(str, result, result_len + 1);
    } else {
        memmove(str, result, max_size - 1);
        str[max_size - 1] = '\0';
    }
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[128] = "1234567890";
    remove_odd_chars(str, sizeof(str));
    printf("%s\n", str);
    return 0;
}