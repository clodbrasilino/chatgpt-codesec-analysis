#include <stdio.h>
#include <math.h>
#include <stdbool.h>

double tetrahedron_area(double a, double b, double c, double d, double e, double f)
{
    double a2 = a * a;
    double b2 = b * b;
    double c2 = c * c;
    double d2 = d * d;
    double e2 = e * e;
    double f2 = f * f;

    double term1 = a2 * b2 * c2;
    double term2 = a2 * d2 * (b2 + c2 + e2 + f2 - a2 - d2);
    double term3 = b2 * e2 * (a2 + c2 + d2 + f2 - b2 - e2);
    double term4 = c2 * f2 * (a2 + b2 + d2 + e2 - c2 - f2);
    double term5 = a2 * b2 * d2 + b2 * c2 * e2 + a2 * c2 * f2 + d2 * e2 * f2;

    double det = term1 + term2 + term3 + term4 - term5;

    if (det < 0.0 && det > -1e-15)
        det = 0.0;
    if (det < 0.0)
        return -1.0;

    return sqrt(det) / 12.0;
}

bool is_valid_tetrahedron(double a, double b, double c, double d, double e, double f)
{
    double s = (a + b + c + d + e + f) / 2.0;
    if (a >= s || b >= s || c >= s || d >= s || e >= s || f >= s)
        return false;

    double vol = tetrahedron_area(a, b, c, d, e, f);
    return vol >= 0.0;
}

int main(void)
{
    double a = 3.0, b = 4.0, c = 5.0, d = 6.0, e = 7.0, f = 8.0;

    if (!is_valid_tetrahedron(a, b, c, d, e, f)) {
        fprintf(stderr, "Invalid tetrahedron edges\n");
        return 1;
    }

    double surface_area = 0.0;

    double faces[4][3] = {
        {a, b, d},
        {a, c, e},
        {b, c, f},
        {d, e, f}
    };

    for (int i = 0; i < 4; ++i) {
        double x = faces[i][0];
        double y = faces[i][1];
        double z = faces[i][2];
        double s2 = (x + y + z) / 2.0;
        double area_sq = s2 * (s2 - x) * (s2 - y) * (s2 - z);
        if (area_sq < 0.0 && area_sq > -1e-15)
            area_sq = 0.0;
        if (area_sq < 0.0) {
            fprintf(stderr, "Invalid face triangle\n");
            return 1;
        }
        surface_area += sqrt(area_sq);
    }

    printf("Surface area: %.10f\n", surface_area);
    return 0;
}