#include <stdio.h>
#include <string.h>

void remove_leading_zeroes(char *ip) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[16] = "";
    char *part = strtok(ip, ".");
    int index = 0;

    while (part != NULL && index < sizeof(temp) - 2) {
        size_t len = strnlen(part, 4);
        if (len > 1 && part[0] == '0') {
            int i;
            for (i = 0; i < len - 1 && part[i] == '0'; i++);
            size_t copy_len = len - i;
            if (index + copy_len < sizeof(temp) - 2) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(temp + index, part + i, copy_len);
                index += copy_len;
            }
        } else {
            if (index + len < sizeof(temp) - 2) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(temp + index, part, len);
                index += len;
            }
        }
        part = strtok(NULL, ".");
        if (part != NULL && index + 1 < sizeof(temp) - 2) {
            temp[index++] = '.';
        };
    }
    temp[index] = '\0';
    snprintf(ip, sizeof(temp), "%s", temp);
}

int main() {
    char ip[] = "192.168.001.001";
    remove_leading_zeroes(ip);
    printf("%s\n", ip);
    return 0;
}