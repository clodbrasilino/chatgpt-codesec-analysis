#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool check_digit_frequency(const char *number) {
    int frequency[10] = {0};
    size_t length;
    size_t i;
    
    if (number == NULL) {
        return false;
    }
    
    length = strlen(number);
    
    if (length == 0) {
        return false;
    }
    
    for (i = 0; i < length; i++) {
        if (number[i] < '0' || number[i] > '9') {
            return false;
        }
        int digit = number[i] - '0';
        frequency[digit]++;
    }
    
    for (i = 0; i < 10; i++) {
        if (frequency[i] > (int)i) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    const char *test_cases[] = {
        "1210",
        "123",
        "111",
        "22",
        "1234",
        "0123",
        "1",
        "0"
    };
    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    size_t i;
    
    for (i = 0; i < num_tests; i++) {
        printf("Number: %s - Result: %s\n", 
               test_cases[i], 
               check_digit_frequency(test_cases[i]) ? "true" : "false");
    }
    
    return 0;
}