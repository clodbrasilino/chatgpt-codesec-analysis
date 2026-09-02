#include <stdio.h>
#include <stdlib.h>

struct Vector3 {
    double x;
    double y;
    double z;
};

static struct Vector3 vector_sub(struct Vector3 a, struct Vector3 b) {
    struct Vector3 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;
}

static struct Vector3 vector_cross(struct Vector3 a, struct Vector3 b) {
    struct Vector3 result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

static double vector_dot(struct Vector3 a, struct Vector3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

static double tetrahedron_volume(struct Vector3 a, struct Vector3 b, struct Vector3 c, struct Vector3 d) {
    struct Vector3 ab = vector_sub(b, a);
    struct Vector3 ac = vector_sub(c, a);
    struct Vector3 ad = vector_sub(d, a);
    struct Vector3 cross = vector_cross(ac, ad);
    double dot = vector_dot(ab, cross);
    double volume = dot / 6.0;
    if (volume < 0.0) {
        volume = -volume;
    }
    return volume;
}

int main(void) {
    struct Vector3 v1;
    struct Vector3 v2;
    struct Vector3 v3;
    struct Vector3 v4;
    double volume;

    v1.x = 0.0;
    v1.y = 0.0;
    v1.z = 0.0;

    v2.x = 1.0;
    v2.y = 0.0;
    v2.z = 0.0;

    v3.x = 0.0;
    v3.y = 1.0;
    v3.z = 0.0;

    v4.x = 0.0;
    v4.y = 0.0;
    v4.z = 1.0;

    volume = tetrahedron_volume(v1, v2, v3, v4);

    if (printf("Volume: %.6f\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}