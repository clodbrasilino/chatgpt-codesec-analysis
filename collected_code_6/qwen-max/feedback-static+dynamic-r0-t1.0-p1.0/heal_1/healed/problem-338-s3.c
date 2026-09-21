#include <stdio.h>
#include <string.h>

long countSubstrings(char *str, size_t length) {
    long count = 0;
    int ascii[256] = {0};

    for (size_t i = 0; i < length; i++) {
        ascii[(unsigned char)str[i]]++;
    }

    for (int i = 0; i < 256; i++) {
        if (ascii[i] > 0) {
            count += (ascii[i] * (ascii[i] + 1L)) / 2;
        }
    }

    return count;
}

int main() {
    char str[] = "abcab";
    printf("Total substrings: %ld\n", countSubstrings(str, sizeof(str) - 1));
    return 0;
}