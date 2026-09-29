#include <stdio.h>
#include <ctype.h>
#include <string.h>

int count_numeric_values(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    int count = 0;
    int in_number = 0;
    
    while (*str) {
        if (isdigit((unsigned char)*str)) {
            if (!in_number) {
                count++;
                in_number = 1;
            }
        } else {
            in_number = 0;
        }
        str++;
    }
    
    return count;
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'test1' can be declared as const array [constVariable]
     */
    char test1[] = "abc123def456";
    /* Possible weaknesses found:
     *  Variable 'test2' can be declared as const array [constVariable]
     */
    char test2[] = "no numbers here";
    /* Possible weaknesses found:
     *  Variable 'test3' can be declared as const array [constVariable]
     */
    char test3[] = "1 2 3 4 5";
    /* Possible weaknesses found:
     *  Variable 'test4' can be declared as const array [constVariable]
     */
    char test4[] = "";
    /* Possible weaknesses found:
     *  Variable 'test5' can be declared as const array [constVariable]
     */
    char test5[] = "1234";
    
    printf("Test 1: %d\n", count_numeric_values(test1));
    printf("Test 2: %d\n", count_numeric_values(test2));
    printf("Test 3: %d\n", count_numeric_values(test3));
    printf("Test 4: %d\n", count_numeric_values(test4));
    printf("Test 5: %d\n", count_numeric_values(test5));
    
    return 0;
}