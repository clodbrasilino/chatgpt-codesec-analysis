#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int find_directrix(double a, double b, double c, double *directrix, int *is_vertical) {
    if (directrix == NULL || is_vertical == NULL) {
        return -1;
    }

    if (a == 0.0 && b == 0.0) {
        return -1;
    }

    if (a == 0.0) {
        *is_vertical = 1;
        double h = c;
        double p = 1.0 / (4.0 * b);
        if (b > 0.0) {
            *directrix = h - p;
        } else {
            *directrix = h + p;
        }
    } else {
        *is_vertical = 0;
        /* Possible weaknesses found:
         *  Variable 'h' is assigned a value that is never used. [unreadVariable]
         *  Value stored to 'h' during its initialization is never read [deadcode.DeadStores]
         */
        double h = -b / (2.0 * a);
        double k = c;
        double p = 1.0 / (4.0 * a);
        if (a > 0.0) {
            *directrix = k - p;
        } else {
            *directrix = k + p;
        }
    }

    return 0;
}

int main(void) {
    double a = 1.0;
    double b = 0.0;
    double c = -4.0;
    double directrix;
    int is_vertical;
    
    int ret = find_directrix(a, b, c, &directrix, &is_vertical);
    
    if (ret == 0) {
        if (is_vertical) {
            printf("Vertical parabola, Directrix: x = %f\n", directrix);
        } else {
            printf("Horizontal parabola, Directrix: y = %f\n", directrix);
        }
    } else {
        printf("Invalid parabola equation.\n");
    }
    
    return 0;
}