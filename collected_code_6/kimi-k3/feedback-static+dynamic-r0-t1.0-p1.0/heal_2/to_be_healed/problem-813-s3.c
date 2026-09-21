#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7, got <no output>
  *  test case 0 failed: expected 6, got <no output>
  *  test case 2 failed: expected 8, got <no output>
  */

size_t string_length(const char *str) {
    size_t length = 0;
    if (str == NULL) {
        return 0;
    }
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[100];
    
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    str[strcspn(str, "\n")] = '\0';
    
    printf("Length of the string: %zu\n", string_length(str));
    
    return 0;
}