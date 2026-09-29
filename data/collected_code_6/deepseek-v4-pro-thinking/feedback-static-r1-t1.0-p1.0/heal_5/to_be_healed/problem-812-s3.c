#include <stdio.h>
#include <stddef.h>

char *abbreviate_road(char *str, size_t size) {
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    size_t len, read, write;

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

    read = 0;
    write = 0;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (read < len) {
        if (read + 3 < len &&
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            str[read] == 'r' &&
            str[read + 1] == 'o' &&
            str[read + 2] == 'a' &&
            str[read + 3] == 'd') {
            str[write++] = 'r';
            str[write++] = 'd';
            str[write++] = '.';
            read += 4;
        } else {
            str[write++] = str[read++];
        }
    }

    str[write] = '\0';
    return str;
}

int main(void) {
    char input[] = "123 main road and broadway road";

    printf("%s\n", input);
    abbreviate_road(input, sizeof(input));
    printf("%s\n", input);

    return 0;
}