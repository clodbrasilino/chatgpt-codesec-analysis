#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int are_permutations(const char *str1, const char *str2) {
    if (strlen(str1) != strlen(str2)) {
        return 0;
    }
    int str_len = strlen(str1);
    int *count = (int *)calloc(256, sizeof(int));
    if (count == NULL) {
        return -1;
    }
    for (int i = 0; i < str_len; i++) {
        count[(unsigned char)str1[i]]++;
        count[(unsigned char)str2[i]]--;
    }
    for (int i = 0; i < 256; i++) {
        if (count[i] != 0) {
            free(count);
            return 0;
        }
    }
    free(count);
    return 1;
}

int main() {
    const char *str1 = "test";
    const char *str2 = "ttew";
    int result = are_permutations(str1, str2);
    if (result == 1) {
        printf("The strings are permutations of each other.\n");
    } else if (result == 0) {
        printf("The strings are not permutations of each other.\n");
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}