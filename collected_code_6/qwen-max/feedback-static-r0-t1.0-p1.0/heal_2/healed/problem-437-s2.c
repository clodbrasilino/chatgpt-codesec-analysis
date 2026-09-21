#include <stdio.h>
#include <string.h>

void remove_odd_chars(char *str) {
    char result[129] = "";
    const char *read = str;
    char *write = result;

    size_t length = strlen(str);

    for (size_t i = 0; i < length; i++) {
        if ((*read - '0') % 2 == 0 || *read < '0' || *read > '9') {
            if (write - result < 128) {
                *write++ = *read;
            }
        }
        read++;
    }
    *write = '\0';
    if (strlen(result) < strlen(str)) {
        strncpy(str, result, sizeof(str));
        str[sizeof(str) - 1] = '\0';
    } else {
        strncpy(str, result, 128);
        str[128 - 1] = '\0';
    }
}

int main() {
    char str[128] = "1234567890";
    remove_odd_chars(str);
    printf("%s\n", str);
    return 0;
}