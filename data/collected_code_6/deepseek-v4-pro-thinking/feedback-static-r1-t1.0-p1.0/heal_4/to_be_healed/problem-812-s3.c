#include <stdio.h>
#include <stddef.h>

char *abbreviate_road(char *str, size_t size) {
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    char *read;
    char *write;
    size_t len;

    if (str == NULL || size == 0) {
        return NULL;
    }

    len = 0;
    while (len < size && str[len] != '\0') {
        len++;
    }
    if (len == size) {
        return NULL;
    }

    read = str;
    write = str;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (*read != '\0') {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (read[1] != '\0' && read[2] != '\0' && read[3] != '\0' &&
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            read[0] == 'r' && read[1] == 'o' && read[2] == 'a' && read[3] == 'd') {
            *write++ = 'r';
            *write++ = 'd';
            *write++ = '.';
            read += 4;
        } else {
            *write++ = *read++;
        }
    }

    *write = '\0';
    return str;
}

int main(void) {
    char input[] = "123 main road and broadway road";

    printf("%s\n", input);
    abbreviate_road(input, sizeof(input));
    printf("%s\n", input);

    return 0;
}