#include <stdio.h>
#include <math.h>
#include <limits.h>

long long find_smallest_triangular_index(int n);

long long find_smallest_triangular_index(int n)
{
    double lower_bound;
    double discriminant;
    long long index;
    long long triangular;

    if (n < 1 || n > 17) {
        return -1;
    }

    if (n == 1) {
        return 1;
    }

    lower_bound = pow(10.0, (double)(n - 1));
    discriminant = sqrt(1.0 + 8.0 * lower_bound);
    index = (long long)ceil((discriminant - 1.0) / 2.0);

    if (index < 1) {
        index = 1;
    }

    while (index > 1) {
        triangular = (index - 1) * index / 2;
        if (triangular >= (long long)lower_bound) {
            index--;
        } else {
            break;
        }
    }

    while (1) {
        if (index > (LLONG_MAX - 1) / index) {
            return -1;
        }
        triangular = index * (index + 1) / 2;
        if ((double)triangular >= lower_bound) {
            break;
        }
        index++;
    }

    return index;
}

int main(void)
{
    int n;
    long long result;
    int scan_status;

    printf("Enter number of digits: ");
    scan_status = scanf("%d", &n);

    if (scan_status != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return 1;
    }

    result = find_smallest_triangular_index(n);

    if (result < 0) {
        fprintf(stderr, "Error: n must be between 1 and 17\n");
        return 1;
    }

    printf("The index of the smallest triangular number with %d digits is %lld\n", n, result);

    return 0;
}