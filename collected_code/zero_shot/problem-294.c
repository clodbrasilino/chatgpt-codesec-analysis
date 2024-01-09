#include <stdio.h>

#define MAX(x, y) ((x > y) ? x : y)

int max_int(int x, int y) {
    return MAX(x, y);
}

double max_double(double x, double y) {
    return MAX(x, y);
}

char max_char(char x, char y) {
    return MAX(x, y);
}

int main() {
    int a = 5, b = 10;
    double c = 2.5, d = 9.7;
    char e = 'A', f = 'Z';

    printf("Max int: %d\n", max_int(a, b));
    printf("Max double: %.2lf\n", max_double(c, d));
    printf("Max char: %c\n", max_char(e, f));

    return 0;
}