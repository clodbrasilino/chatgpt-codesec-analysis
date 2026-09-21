#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sort_string(char *str) {
    size_t len = strnlen(str, 1024);
    if (len >= 1024) {
        fprintf(stderr, "String too long\n");
        exit(1);
    }
    char *temp = (char *)malloc(len + 1);
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(temp, str, len + 1);

    for (int i = 0; i < len - 1; ++i) {
        for (int j = i + 1; j < len; ++j) {
            if (temp[i] > temp[j]) {
                char c = temp[i];
                temp[i] = temp[j];
                temp[j] = c;
            }
        }
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(str, temp, len + 1);
    free(temp);
}

int main() {
    char str[] = "programming";
    printf("Original string: %s\n", str);
    sort_string(str);
    printf("Sorted string: %s\n", str);
    return 0;
}