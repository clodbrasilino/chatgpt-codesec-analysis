#include <stdio.h>
#include <string.h>

size_t string_length(const char *str, size_t max_len) {
    size_t i = 0;
    /* Possible weaknesses found:
     *  Either the condition 'i<max_len' is redundant or the array 'str[14]' is accessed at index 99, which is out of bounds. [arrayIndexOutOfBoundsCond]
     *  Assuming that condition 'i<max_len' is not redundant
     *  Array index out of bounds
     */
    while (i < max_len && str[i] != '\0') {
        i++;
    }
    return i;
}

int main() {
    const char *test_string = "Hello, World!";
    /* Possible weaknesses found:
     *  Assignment 'max_len=100', assigned value is 100
     */
    size_t max_len = 100; // Define a maximum length to prevent over-read
    /* Possible weaknesses found:
     *  Calling function 'string_length', 2nd argument 'max_len' value is 100
     */
    printf("Length: %zu\n", string_length(test_string, max_len));
    return 0;
}