#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    if (a <= 0 || b <= 0) {
        return 0;
    }
    return (a / gcd(a, b)) * b;
}

int find_numbers(int low, int high, int *x, int *y) {
    if (low <= 0 || high <= 0 || low > high || x == NULL || y == NULL) {
        return -1;
    }

    for (int i = low; i <= high; i++) {
        for (int j = i + 1; j <= high; j++) {
            int current_lcm = lcm(i, j);
            if (current_lcm >= low && current_lcm <= high) {
                *x = i;
                *y = j;
                return 0;
            }
        }
    }

    return -1;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <low> <high>\n", argv[0]);
        return 1;
    }

    long long low_ll = strtoll(argv[1], NULL, 10);
    long long high_ll = strtoll(argv[2], NULL, 10);

    if (low_ll <= 0 || high_ll <= 0 || low_ll > high_ll || low_ll > 2147483647 || high_ll > 2147483647) {
        fprintf(stderr, "Invalid range\n");
        return 1;
    }

    int low = (int)low_ll;
    int high = (int)high_ll;

    int x, y;
    if (find_numbers(low, high, &x, &y) == 0) {
        printf("%d %d\n", x, y);
    } else {
        printf("No such numbers found\n");
    }

    return 0;
}