#include <stdio.h>
#include <string.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected True, got <no output>
  *  test case 2 failed: expected False, got <no output>
  *  test case 0 failed: expected False, got <no output>
  */

bool all_characters_same(const char *str) {
    if (str == NULL || str[0] == '\0') {
        return false;
    }
    
    char first = str[0];
    size_t i = 1;
    
    while (str[i] != '\0') {
        if (str[i] != first) {
            return false;
        }
        i++;
    }
    
    return true;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    
    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    buffer[strcspn(buffer, "\n")] = '\0';
    
    if (all_characters_same(buffer)) {
        printf("All characters are the same\n");
    } else {
        printf("Characters are not all the same\n");
    }
    
    return 0;
}