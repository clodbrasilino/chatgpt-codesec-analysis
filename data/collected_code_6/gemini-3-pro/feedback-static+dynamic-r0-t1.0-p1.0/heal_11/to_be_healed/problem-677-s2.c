#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected True, got 0
  *  test case 0 failed: expected False, got 1
  */

bool is_valid_triangle(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return false;
    }
    return (a + b > c) && (a + c > b) && (b + c > a);
}

int main(int argc, const char *argv[]) {
    double a = 0.0, b = 0.0, c = 0.0;
    int parsed = 0;

    if (argc > 3) {
        a = atof(argv[1]);
        b = atof(argv[2]);
        c = atof(argv[3]);
        parsed = 3;
    } else {
        char buffer[1024];
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            for (int i = 0; buffer[i] != '\0'; i++) {
                if (buffer[i] == ',' || buffer[i] == ';') {
                    buffer[i] = ' ';
                }
            }
            parsed = sscanf(buffer, "%lf %lf %lf", &a, &b, &c);
        }
    }

    if (parsed == 3 && is_valid_triangle(a, b, c)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}