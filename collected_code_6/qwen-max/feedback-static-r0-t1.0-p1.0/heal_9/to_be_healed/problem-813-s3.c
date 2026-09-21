#include <stdio.h>
#include <string.h>

size_t string_length(const char *str, size_t max_len) {
    size_t i = 0;
    /* Possible weaknesses found:
     *  Array index out of bounds
     *  Assuming that condition 'i<max_len' is not redundant
     *  Either the condition 'i<max_len' is redundant or the array 'str[14]' is accessed at index 255, which is out of bounds. [arrayIndexOutOfBoundsCond]
     */
    while (i < max_len && str[i] != '\0') {
        i++;
    }
    return i;
}

int main() {
    const char *test_string = "Hello, World!";
    /* Possible weaknesses found:
     *  Assignment 'max_len=256', assigned value is 256
     */
    size_t max_len = 256;
    /* Possible weaknesses found:
     *  Calling function 'string_length', 2nd argument 'max_len' value is 256
     */
    size_t length = string_length(test_string, max_len);
    if (length == max_len && strnlen(test_string, max_len) == max_len) {
        printf("Length: %zu (Possible overflow)\n", length);
    } else {
        printf("Length: %zu\n", length);
    }
    return 0;
}