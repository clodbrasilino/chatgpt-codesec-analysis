#include <stdio.h>
#include <stdlib.h>

int sum_of_digits(long n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

long divide_into_two_parts(long number, long *part1, long *part2) {
    long max_sum = -1;
    long final_part1 = 0, final_part2 = 0;

    for (long i = 0; i <= 9; ++i) {
        for (long j = 0; j <= 9; ++j) {
            for (long p1 = 0; p1 <= number; p1 += 10) {
                for (long p2 = 0; p2 <= number; p2 += 10) {
                    if (p1 + p2 == number && p1 % 10 == i && p2 % 10 == j) {
                        int s1 = sum_of_digits(p1);
                        int s2 = sum_of_digits(p2);
                        if (s1 + s2 > max_sum) {
                            max_sum = s1 + s2;
                            final_part1 = p1;
                            final_part2 = p2;
                        }
                    }
                }
            }
        }
    }

    *part1 = final_part1;
    *part2 = final_part2;
    return max_sum;
}

int main() {
    long number = 12345;
    long part1, part2;
    long max_sum = divide_into_two_parts(number, &part1, &part2);
    printf("Number: %ld\n", number);
    printf("Part 1: %ld, Part 2: %ld\n", part1, part2);
    printf("Max Sum of Digits: %ld\n", max_sum);
    return 0;
}