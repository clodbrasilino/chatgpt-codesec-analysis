#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* find_demlo_number(int n) {
    if (n <= 0) {
        return NULL;
    }

    int len = 0;
    for (int temp = n; temp > 0; temp /= 10) {
        len++;
    }

    char* result = (char*)malloc(len * 2 + 1);
    if (result == NULL) {
        return NULL;
    }

    int index = 0;
    int current_num = 0;
    for (int i = 1; i <= n; i *= 10) {
        current_num = current_num * 10 + 1;
        int s_len = 0;
        int temp = current_num * current_num;
        for (int t = temp; t > 0; t /= 10) {
            s_len++;
        }

        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char buffer[32];
        snprintf(buffer, 32, "%d", temp);

        for (int j = 0; j < s_len; j++) {
            result[index++] = buffer[j];
        }
    }

    result[index] = '\0';
    return result;
}

int main() {
    int n = 3;
    char* demlo = find_demlo_number(n);
    if (demlo != NULL) {
        printf("%s\n", demlo);
        free(demlo);
    }
    return 0;
}