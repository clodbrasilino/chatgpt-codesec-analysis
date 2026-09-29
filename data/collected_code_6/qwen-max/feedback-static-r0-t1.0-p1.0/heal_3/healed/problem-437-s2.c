#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void remove_odd_chars(char *str, size_t size) {
    char result[129] = "";
    const char *read = str;
    char *write = result;

    for (size_t i = 0; i < size && read[i] != '\0'; i++) {
        if ((read[i] - '0') % 2 == 0 || read[i] < '0' || read[i] > '9') {
            if (write - result < 128) {
                *write++ = read[i];
            }
        }
    }
    *write = '\0';

    if (strlen(result) < size && result[size - 1] != '\0') {
        memcpy(str, result, sizeof(result));
        str[sizeof(result) - 1] = '\0';
    } else {
        memcpy(str, result, 128);
        str[128 - 1] = '\0';
    }
}

int main() {
    char str[128] = "1234567890";
    remove_odd_chars(str, sizeof(str));
    printf("%s\n", str);
    return 0;
}