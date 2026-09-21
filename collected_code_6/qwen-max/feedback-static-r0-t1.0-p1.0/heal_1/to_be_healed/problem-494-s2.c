#include <stdio.h>
#include <string.h>

int binary_tuple_to_integer(const char *binary) {
    int result = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    for (int i = 0; i < strlen(binary); ++i) {
        result = (result << 1) | (binary[i] - '0');
    }
    return result;
}

int main() {
    const char *binary_tuple = "1101";
    int integer_value = binary_tuple_to_integer(binary_tuple);
    printf("%d\n", integer_value);
    return 0;
}