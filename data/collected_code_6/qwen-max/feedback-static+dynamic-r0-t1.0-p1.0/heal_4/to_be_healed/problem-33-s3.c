#include <stdio.h>
#include <string.h>
#include <limits.h>

void decimalToBinary(int n, char *buffer, int bufferSize) {
    if (n < 0 || n > INT_MAX || bufferSize < 2) return;
    int i = 0;
    while (n > 0 && i < bufferSize - 1) {
        buffer[i++] = (n % 2) + '0';
        n /= 2;
    }
    buffer[i] = '\0';
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(buffer);
    for (int j = 0; j < len / 2; j++) {
        char temp = buffer[j];
        buffer[j] = buffer[len - j - 1];
        buffer[len - j - 1] = temp;
    }
}

int main() {
    int num = 10;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[33];
    decimalToBinary(num, binary, sizeof(binary));
    printf("%s\n", binary);
    return 0;
}