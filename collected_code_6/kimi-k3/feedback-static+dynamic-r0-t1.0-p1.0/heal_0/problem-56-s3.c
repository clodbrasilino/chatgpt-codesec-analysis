#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int reverse_number(int num) {
    int reversed = 0;
    int is_negative = 0;
    
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }
    
    while (num != 0) {
        if (reversed > (INT_MAX - num % 10) / 10) {
            return 0;
        }
        reversed = reversed * 10 + num % 10;
        num /= 10;
    }
    
    return is_negative ? -reversed : reversed;
}

int is_one_less_than_twice_reverse(int num) {
    int reversed = reverse_number(num);
    
    if (reversed > INT_MAX / 2) {
        return 0;
    }
    
    return num == 2 * reversed - 1;
}

int main(void) {
    int num;
    char input[100];
    
    printf("Enter a number: ");
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    char *endptr;
    errno = 0;
    long value = strtol(input, &endptr, 10);
    
    if (errno != 0 || endptr == input || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (value < INT_MIN || value > INT_MAX) {
        fprintf(stderr, "Number out of range\n");
        return EXIT_FAILURE;
    }
    
    num = (int)value;
    
    if (is_one_less_than_twice_reverse(num)) {
        printf("%d is one less than twice its reverse.\n", num);
    } else {
        printf("%d is not one less than twice its reverse.\n", num);
    }
    
    return EXIT_SUCCESS;
}