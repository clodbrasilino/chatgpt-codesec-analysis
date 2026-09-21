#include <stdio.h>
#include <string.h>

long countSubstrings(const char *str, size_t len) {
    long count = 0;
    int ascii[256] = {0};

    for (size_t i = 0; i < len; i++) {
        ascii[(unsigned char)str[i]]++;
    }

    for (int i = 0; i < 256; i++) {
        if (ascii[i] > 0) {
            count += (long)ascii[i] * (ascii[i] + 1L) / 2;
        }
    }

    return count;
}

int main() {
    const char str[] = "abcab";
    size_t len = sizeof(str) - 1;
    printf("Total substrings: %ld\n", countSubstrings(str, len));
    return 0;
}