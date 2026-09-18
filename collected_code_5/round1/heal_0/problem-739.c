#include <stdio.h>
#include <math.h>
#include <stdlib.h>

unsigned long long find_index_of_smallest_n_digit_triangular_num(int num_digits) {
    unsigned long long index;
    unsigned long long pow_of_10;
   
    if(num_digits > 0) {
        pow_of_10= pow(10, num_digits - 1);
        index = ceil((sqrt(8*pow_of_10 + 1) - 1)/2);
    } 
    else {
        printf("Error: Number of digits must be larger than 0\n");
        exit(EXIT_FAILURE);
    }
    
    return index;
}

int main() {
    int num_digits;
    unsigned long long index;
    printf("Please enter a number of digits: ");
    scanf("%d", &num_digits);
    index = find_index_of_smallest_n_digit_triangular_num(num_digits);
    printf("The index of the smallest triangular number with %d digits is: %llu\n", num_digits, index);
    return 0;
}