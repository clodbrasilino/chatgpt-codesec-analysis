#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
    double z;
} Point3D;

static double tetrahedron_volume(const Point3D *a, const Point3D *b,
                                 const Point3D *c, const Point3D *d)
{
    double v1x = b->x - a->x;
    double v1y = b->y - a->y;
    double v1z = b->z - a->z;
    double v2x = c->x - a->x;
    double v2y = c->y - a->y;
    double v2z = c->z - a->z;
    double v3x = d->x - a->x;
    double v3y = d->y - a->y;
    double v3z = d->z - a->z;

    double det = v1x * (v2y * v3z - v2z * v3y)
               - v1y * (v2x * v3z - v2z * v3x)
               + v1z * (v2x * v3y - v2y * v3x);

    return fabs(det) / 6.0;
}

static int read_point(const char *label, Point3D *p)
{
    printf("Enter coordinates of point %s (x y z): ", label);
    if (scanf("%lf %lf %lf", &p->x, &p->y, &p->z) != 3) {
        fprintf(stderr, "Error: invalid input for point %s.\n", label);
        return -1;
    }
    return 0;
}

int main(void)
{
    Point3D a;
    Point3D b;
    Point3D c;
    Point3D d;
    double volume;

    if (read_point("A", &a) != 0) {
        return EXIT_FAILURE;
    }
    if (read_point("B", &b) != 0) {
        return EXIT_FAILURE;
    }
    if (read_point("C", &c) != 0) {
        return EXIT_FAILURE;
    }
    if (read_point("D", &d) != 0) {
        return EXIT_FAILURE;
    }

    volume = tetrahedron_volume(&a, &b, &c, &d);

    if (volume == 0.0) {
        printf("The given points are coplanar; the tetrahedron is degenerate (volume = 0).\n");
    } else {
        printf("Volume of the tetrahedron: %.6f\n", volume);
    }

    return EXIT_SUCCESS;
}