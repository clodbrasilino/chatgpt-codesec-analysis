#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
    double z;
} Point3D;

double tetrahedron_volume(const Point3D *a, const Point3D *b,
                          const Point3D *c, const Point3D *d)
{
    double ux = b->x - a->x;
    double uy = b->y - a->y;
    double uz = b->z - a->z;
    double vx = c->x - a->x;
    double vy = c->y - a->y;
    double vz = c->z - a->z;
    double wx = d->x - a->x;
    double wy = d->y - a->y;
    double wz = d->z - a->z;

    double det = ux * (vy * wz - vz * wy)
               - uy * (vx * wz - vz * wx)
               + uz * (vx * wy - vy * wx);

    return fabs(det) / 6.0;
}

static int read_point(const char *label, Point3D *p)
{
    printf("Enter coordinates of point %s (x y z): ", label);
    if (scanf("%lf %lf %lf", &p->x, &p->y, &p->z) != 3) {
        fprintf(stderr, "Error: invalid input for point %s.\n", label);
        return -1;
    }
    if (!isfinite(p->x) || !isfinite(p->y) || !isfinite(p->z)) {
        fprintf(stderr, "Error: non-finite value for point %s.\n", label);
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

    if (!isfinite(volume)) {
        fprintf(stderr, "Error: computation overflowed.\n");
        return EXIT_FAILURE;
    }

    if (volume == 0.0) {
        printf("The points are coplanar; the tetrahedron is degenerate.\n");
    } else {
        printf("Volume of the tetrahedron: %.6f\n", volume);
    }

    return EXIT_SUCCESS;
}