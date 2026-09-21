#include <stdio.h>
#include <ctype.h>
#include <string.h>

void find_sequences(const char *str, size_t len) {
    for (size_t i = 0; i < len; ) {
        if (isupper((unsigned char)str[i])) {
            size_t start = i;
            i++;
            while (i < len && islower((unsigned char)str[i])) {
                i++;
            }
            if (i > start + 1) {
                printf("%.*s\n", (int)(i - start), &str[start]);
            } else {
                i = start + 1;
            }
        } else {
            i++;
        }
    }
}

int main() {
    const char *input = "ThisIsAnExample AbCdef Another ExampleA";
    size_t input_len = strlen(input);
    find_sequences(input, input_len);
    return 0;
}