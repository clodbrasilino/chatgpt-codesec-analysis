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

    if (argc >= 4) {
        a = atof(argv[1]);
        b = atof(argv[2]);
        c = atof(argv[3]);
    } else {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char buffer[2048] = {0};
        if (fgets(buffer, sizeof(buffer), stdin)) {
            char *p = buffer;
            while (*p && !isdigit((unsigned char)*p) && *p != '-' && *p != '+' && *p != '.') p++;
            a = strtod(p, &p);
            while (*p && !isdigit((unsigned char)*p) && *p != '-' && *p != '+' && *p != '.') p++;
            b = strtod(p, &p);
            while (*p && !isdigit((unsigned char)*p) && *p != '-' && *p != '+' && *p != '.') p++;
            c = strtod(p, &p);
        }
    }

    if (is_valid_triangle(a, b, c)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}