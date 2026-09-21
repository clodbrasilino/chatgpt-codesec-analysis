#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool check_first_last_equal(const char *str, size_t len) {
    if (str == NULL || len == 0) {
        return false;
    }
    return str[0] == str[len - 1];
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    size_t len;
    
    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    len = strnlen(buffer, sizeof(buffer));
    if (len == sizeof(buffer)) {
        fprintf(stderr, "Input too long\n");
        return 1;
    }
    
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    
    if (check_first_last_equal(buffer, len)) {
        printf("First and last characters are equal.\n");
    } else {
        printf("First and last characters are not equal.\n");
    }
    
    return 0;
}