#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sort_string(char *str) {
    size_t len = strnlen(str, 1024);
    char *temp = (char *)malloc(len + 1);
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, str, len + 1);

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
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str, temp, len + 1);
    free(temp);
}

int main() {
    char str[] = "programming";
    printf("Original string: %s\n", str);
    sort_string(str);
    printf("Sorted string: %s\n", str);
    return 0;
}