#include <stdio.h>

void decode_run_length(const char *encoded_list) {
    int length;
    char letter;

    for (int i = 0; encoded_list[i] != '\0' && encoded_list[i+1] != '\0'; i += 2) {
        length = encoded_list[i] - '0';
        letter = encoded_list[i + 1];

        for (int j = 0; j < length; j++) {
            printf("%c", letter);
        }
    }
}

int main() {
    const char encoded_list[] = "3a5b2c";
    decode_run_length(encoded_list);

    return 0;
}