#include <stdio.h>
#include <math.h>

double calculate_tetrahedron_volume(double x1, double y1, double z1,
                                    double x2, double y2, double z2,
                                    double x3, double y3, double z3,
                                    double x4, double y4, double z4)
{
    double ax = x2 - x1;
    double ay = y2 - y1;
    double az = z2 - z1;

    double bx = x3 - x1;
    double by = y3 - y1;
    double bz = z3 - z1;

    double cx = x4 - x1;
    double cy = y4 - y1;
    double cz = z4 - z1;

    double cross_x = by * cz - bz * cy;
    double cross_y = bz * cx - bx * cz;
    double cross_z = bx * cy - by * cx;

    double scalar_triple = ax * cross_x + ay * cross_y + az * cross_z;

    return fabs(scalar_triple) / 6.0;
}

int main(void)
{
    double x1, y1, z1;
    double x2, y2, z2;
    double x3, y3, z3;
    double x4, y4, z4;
    double volume;
    int scan_result;

    printf("Enter coordinates of vertex 1 (x y z): ");
    scan_result = scanf("%lf %lf %lf", &x1, &y1, &z1);
    if (scan_result != 3)
    {
        fprintf(stderr, "Invalid input for vertex 1.\n");
        return 1;
    }

    printf("Enter coordinates of vertex 2 (x y z): ");
    scan_result = scanf("%lf %lf %lf", &x2, &y2, &z2);
    if (scan_result != 3)
    {
        fprintf(stderr, "Invalid input for vertex 2.\n");
        return 1;
    }

    printf("Enter coordinates of vertex 3 (x y z): ");
    scan_result = scanf("%lf %lf %lf", &x3, &y3, &z3);
    if (scan_result != 3)
    {
        fprintf(stderr, "Invalid input for vertex 3.\n");
        return 1;
    }

    printf("Enter coordinates of vertex 4 (x y z): ");
    scan_result = scanf("%lf %lf %lf", &x4, &y4, &z4);
    if (scan_result != 3)
    {
        fprintf(stderr, "Invalid input for vertex 4.\n");
        return 1;
    }

    volume = calculate_tetrahedron_volume(x1, y1, z1,
                                          x2, y2, z2,
                                          x3, y3, z3,
                                          x4, y4, z4);

    printf("Volume of the tetrahedron: %.6f\n", volume);

    return 0;
}