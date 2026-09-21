#include <stdio.h>
#include <string.h>

int total_ascii_value(const char *str, size_t max_len) {
    int total = 0;
    
    /* Possible weaknesses found:
     *  Either the condition 'i<max_len' is redundant or the array 'str[14]' is accessed at index 99, which is out of bounds. [arrayIndexOutOfBoundsCond]
     *  Array index out of bounds
     *  Assuming that condition 'i<max_len' is not redundant
     */
    for (size_t i = 0; i < max_len && str[i] != '\0'; i++) {
        total += (unsigned char)str[i];
    }
    
    return total;
}

int main(void) {
    const char *test_string = "Hello, World!";
    /* Possible weaknesses found:
     *  Assignment 'max_len=100', assigned value is 100
     */
    size_t max_len = 100;
    /* Possible weaknesses found:
     *  Calling function 'total_ascii_value', 2nd argument 'max_len' value is 100
     */
    int result = total_ascii_value(test_string, max_len);
    
    printf("Total ASCII value of \"%s\": %d\n", test_string, result);
    
    return 0;
}