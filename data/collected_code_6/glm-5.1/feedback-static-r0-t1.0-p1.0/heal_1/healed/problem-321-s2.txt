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
        int temp = current_num * current_num;

        int written = snprintf(result + index, len * 2 + 1 - index, "%d", temp);
        if (written > 0) {
            index += written;
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