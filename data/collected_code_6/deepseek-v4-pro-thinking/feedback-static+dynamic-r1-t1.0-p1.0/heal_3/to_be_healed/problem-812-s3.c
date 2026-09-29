#include <stdio.h>
#include <string.h>
#include <stddef.h>

char *abbreviate_road(char *str, size_t size) {
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    char *read;
    char *write;
    const char *end;

    if (str == NULL || size == 0) {
        return NULL;
    }

    read = str;
    write = str;
    end = str + size;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (read < end && *read != '\0') {
        if (read + 4 <= end &&
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            read[1] != '\0' &&
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            read[2] != '\0' &&
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            read[3] != '\0' &&
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            memcmp(read, "road", 4) == 0) {
            *write++ = 'r';
            *write++ = 'd';
            *write++ = '.';
            read += 4;
        } else {
            *write++ = *read++;
        }
    }

    if (write < end) {
        *write = '\0';
    } else {
        /* Possible weaknesses found:
         *  read-only variable is not assignable
         *  assignment of read-only location '*(end + -1)'
         */
        *(end - 1) = '\0';
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