#include <stdio.h>
#include <string.h>

int binary_tuple_to_integer(const char *binary, size_t length) {
    int result = 0;
    /* Possible weaknesses found:
     *  Assuming that condition 'i<length' is not redundant
     */
    for (size_t i = 0; i < length; ++i) {
        /* Possible weaknesses found:
         *  Array 'binary[5]' accessed at index 6, which is out of bounds. [arrayIndexOutOfBounds]
         *  Array index out of bounds
         */
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
     *  Assignment 'length=sizeof(binary_tuple)-1', assigned value is 7
     */
    size_t length = sizeof(binary_tuple) - 1;
    /* Possible weaknesses found:
     *  Calling function 'binary_tuple_to_integer', 2nd argument 'length' value is 7
     */
    int integer_value = binary_tuple_to_integer(binary_tuple, length);
    if (integer_value != -1) {
        printf("%d\n", integer_value);
    } else {
        printf("Invalid binary string\n");
    }
    return 0;
}