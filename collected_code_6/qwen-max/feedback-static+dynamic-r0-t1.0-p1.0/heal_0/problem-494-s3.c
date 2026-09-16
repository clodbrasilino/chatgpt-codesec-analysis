#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint32_t binary_tuple_to_int(const char *binary, size_t length) {
    uint32_t result = 0;
    for (size_t i = 0; i < length; ++i) {
        if (binary[i] == '1') {
            result |= 1 << (length - i - 1);
        }
    }
    return result;
}

int main() {
    const char *binary_tuple = "1101";
    size_t length = strlen(binary_tuple);
    uint32_t integer_value = binary_tuple_to_int(binary_tuple, length);
    printf("The integer value is: %u\n", integer_value);
    return 0;
}