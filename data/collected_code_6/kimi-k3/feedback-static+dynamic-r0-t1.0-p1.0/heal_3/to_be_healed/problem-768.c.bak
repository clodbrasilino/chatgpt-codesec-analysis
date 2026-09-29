#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 1 failed: expected True, got <no output>
  *  test case 0 failed: expected True, got <no output>
  */

int check_odd_parity(unsigned int num)
{
    int parity = 0;
    
    while (num != 0U) {
        parity ^= 1;
        num &= (num - 1U);
    }
    
    return parity;
}

int main(void)
{
    char buffer[256];
    char *endptr;
    unsigned long value;
    unsigned int num;
    int result;
    size_t len;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        fprintf(stderr, "Empty input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    value = strtoul(buffer, &endptr, 10);
    
    if (errno != 0) {
        fprintf(stderr, "Error converting input\n");
        return EXIT_FAILURE;
    }
    
    if (endptr == buffer) {
        fprintf(stderr, "No digits found\n");
        return EXIT_FAILURE;
    }
    
    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) {
            fprintf(stderr, "Invalid characters in input\n");
            return EXIT_FAILURE;
        }
        endptr++;
    }
    
    if (value > UINT_MAX) {
        fprintf(stderr, "Value out of range\n");
        return EXIT_FAILURE;
    }
    
    num = (unsigned int)value;
    result = check_odd_parity(num);
    
    if (result == 1) {
        printf("true\n");
    } else {
        printf("false\n");
    }
    
    return EXIT_SUCCESS;
}