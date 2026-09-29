#include <stdio.h>
#include <string.h>

char *abbreviate_road(char *str) {
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    char *read;
    char *write;

    if (str == NULL) {
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
        if (strncmp(read, "road", 4) == 0) {
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
    abbreviate_road(input);
    printf("%s\n", input);

    return 0;
}