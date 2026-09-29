#include <stdio.h>
#include <stddef.h>
#include <string.h>

char *abbreviate_road(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return NULL;
    }

    size_t len = strnlen(str, size);
    if (len == size) {
        return NULL;
    }

    size_t read = 0;
    size_t write = 0;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (read < len) {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (read + 4 <= len && memcmp(&str[read], "road", 4) == 0) {
            if (write + 3 < size) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(&str[write], "rd.", 3);
                write += 3;
                read += 4;
            } else {
                break;
            }
        } else {
            if (write + 1 < size) {
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                str[write] = str[read];
                ++write;
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ++read;
            } else {
                break;
            }
        }
    }

    if (write < size) {
        str[write] = '\0';
    } else {
        str[size - 1] = '\0';
    }

    return str;
}

int main(void) {
    char input[] = "123 main road and broadway road";
    printf("%s\n", input);
    abbreviate_road(input, sizeof(input));
    printf("%s\n", input);
    return 0;
}