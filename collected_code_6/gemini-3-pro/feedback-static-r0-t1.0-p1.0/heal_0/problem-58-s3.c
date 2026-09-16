#include <stdio.h>
#include <stdbool.h>

bool hasOppositeSigns(int x, int y) {
    return (x < 0) != (y < 0);
}

int main(void) {
    int test_pairs[][2] = {
        {100, -100},
        {-50, 50},
        {10, 20},
        {-10, -20},
        {0, -1},
        {0, 1}
    };
    int num_pairs = sizeof(test_pairs) / sizeof(test_pairs[0]);

    for (int i = 0; i < num_pairs; i++) {
        int x = test_pairs[i][0];
        int y = test_pairs[i][1];
        if (hasOppositeSigns(x, y)) {
            printf("%d and %d have opposite signs.\n", x, y);
        } else {
            printf("%d and %d do not have opposite signs.\n", x, y);
        }
    }

    return 0;
}