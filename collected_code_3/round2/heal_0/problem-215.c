#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* decode(const char* encoded) {
    int length = strlen(encoded);
    char* decoded = (char*)malloc(length * sizeof(char));
    int i, j = 0, count;
    char ch;

    for (i = 0; i < length; i++) {
        ch = encoded[i];
        i++;
        count = encoded[i] - '0';
        while (count > 0) {
            decoded[j] = ch;
            j++;
            count--;
        }
    }
    decoded[j] = '\0';
    return decoded;
}

int main() {
    const char* encoded = "a2b3c4";
    char* decoded = decode(encoded);
    printf("Decoded string: %s\n", decoded);
    free(decoded);
    return 0;
}