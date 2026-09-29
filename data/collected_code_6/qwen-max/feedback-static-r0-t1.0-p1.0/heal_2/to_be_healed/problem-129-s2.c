#include <stdio.h>
#include <stdlib.h>

void generate_magic_square(int n, int magic[][10]) {
    int i, num = 1;
    int x = n / 2, y = n - 1;

    for (i = 0; i < n * n; ++i) {
        if (x == -1 && y == n) { 
            x = 0;
            y = n - 2;
        } else if (x < 0) {
            x = n - 1;
        } else if (y == n) {
            y = 0;
        }
        
        if (magic[x][y] > 0) {
            y -= 2;
            x++;
            continue;
        }

        magic[x][y] = num++;
        y++;
        x--;
    }
}

int main() {
    int n = 3;

    generate_magic_square(n, (int [10][10]){0});

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            /* Possible weaknesses found:
             *  each undeclared identifier is reported only once for each function it appears in
             *  use of undeclared identifier 'magic'
             *  'magic' undeclared (first use in this function)
             */
            printf("%d ", magic[i][j]);
        }
        printf("\n");
    }

    return 0;
}