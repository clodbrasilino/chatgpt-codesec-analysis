#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* move_numbers_to_given_string(const char* input, char* output) {
    int index = 0;
    for (int i = 0; input[i] != '\0'; ++i) {
        if (input[i] >= '0' && input[i] <= '9') {
            output[index++] = input[i];
        }
    }
    output[index] = '\0';
    return output;
}

int main() {
    const char* input = "Hello123World456";
    char output[50] = "";
    move_numbers_to_given_string(input, output);
    printf("Numbers: %s\n", output);
    return 0;
}