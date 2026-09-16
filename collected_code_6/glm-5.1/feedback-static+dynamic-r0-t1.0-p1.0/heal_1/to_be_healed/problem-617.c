#include <stdio.h>
#include <stdlib.h>

int calculate_jumps(int a, int b, int d) {
    if (a <= 0 || b <= 0) {
        return -1;
    }
    if (d < 0) {
        return -1;
    }
    if (d == 0) {
        return 0;
    }
    if (d % a == 0) {
        return d / a;
    }
    if (a > b) {
        int max_forward_jumps = d / a;
        /* Possible weaknesses found:
         *  Variable 'remainder' is assigned a value that is never used. [unreadVariable]
         *  Value stored to 'remainder' during its initialization is never read [deadcode.DeadStores]
         */
        int remainder = d % a;
        for (int i = max_forward_jumps; i >= 0; i--) {
            int current_dist = i * a;
            if (current_dist <= d) {
                int diff = d - current_dist;
                if (diff % b == 0) {
                    return i + (diff / b);
                }
            } else {
                int diff = current_dist - d;
                if (diff % b == 0) {
                    return i + (diff / b);
                }
            }
        }
    }
    if (d % b == 0) {
        return d / b;
    }
    return -1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 4) {
        return EXIT_FAILURE;
    }
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int d = atoi(argv[3]);
    int result = calculate_jumps(a, b, d);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}