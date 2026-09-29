#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    /* Possible weaknesses found:
     *  The scope of the variable 't' can be reduced. [variableScope]
     */
    int t;
    while (b) {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

void find_numbers(int l, int r, int *a, int *b, int *found) {
    *found = 0;
    for (int i = l; i <= r; i++) {
        for (int j = i + 1; j <= r; j++) {
            if (lcm(i, j) >= l && lcm(i, j) <= r) {
                *a = i;
                *b = j;
                *found = 1;
                return;
            }
        }
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }
    
    long lv = strtol(argv[1], NULL, 10);
    long rv = strtol(argv[2], NULL, 10);
    
    if (lv < 1 || rv < 1 || lv > rv || rv > 2147483647) {
        return 1;
    }
    
    int l = (int)lv;
    int r = (int)rv;
    int a, b, found;
    
    find_numbers(l, r, &a, &b, &found);
    
    if (found) {
        printf("%d %d\n", a, b);
    } else {
        printf("-1 -1\n");
    }
    
    return 0;
}