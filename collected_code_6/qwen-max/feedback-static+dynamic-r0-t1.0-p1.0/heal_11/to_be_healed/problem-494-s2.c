#include <stdio.h>
#include <string.h>

int binary_tuple_to_integer(const char *binary, size_t length) {
    int result = 0;
    for (size_t i = 0; i < length; ++i) {
        if (binary[i] == '0' || binary[i] == '1') {
            result = (result << 1) | (binary[i] - '0');
        } else {
            return -1;
        }
    }
    return result;
}

int main() {
    const char *binary_tuple = "1101";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(binary_tuple);
    int integer_value = binary_tuple_to_integer(binary_tuple, length);
    if (integer_value != -1) {
        printf("%d\n", integer_value);
    } else {
        printf("Invalid binary string\n");
    }
    return 0;
}