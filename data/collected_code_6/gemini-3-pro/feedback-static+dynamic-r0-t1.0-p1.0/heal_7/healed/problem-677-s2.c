#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

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
        char *buffer = NULL;
        size_t bufsize = 0;
        
        if (getline(&buffer, &bufsize, stdin) != -1) {
            for (int i = 0; buffer[i] != '\0'; i++) {
                if (buffer[i] == ',') {
                    buffer[i] = ' ';
                }
            }
            sscanf(buffer, "%lf %lf %lf", &a, &b, &c);
        }
        free(buffer);
    }

    if (is_valid_triangle(a, b, c)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}