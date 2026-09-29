#include <stdio.h>

long find_nth_term(long a, long d, long n) {
    return a + (n - 1) * d;
}

int main() {
    long first_term = 1;
    long common_difference = 2;
    long term_position = 10;

    long nth_term = find_nth_term(first_term, common_difference, term_position);
    printf("The %ldth term of the arithmetic progression is: %ld\n", term_position, nth_term);

    return 0;
}