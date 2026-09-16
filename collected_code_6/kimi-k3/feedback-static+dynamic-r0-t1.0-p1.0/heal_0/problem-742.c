#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
    double z;
} Point3D;

double calculate_distance(Point3D p1, Point3D p2) {
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double dz = p2.z - p1.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

double calculate_triangle_area(double a, double b, double c) {
    double s = (a + b + c) / 2.0;
    double area_squared = s * (s - a) * (s - b) * (s - c);
    
    if (area_squared < 0.0) {
        return -1.0;
    }
    
    return sqrt(area_squared);
}

double calculate_tetrahedron_surface_area(Point3D vertices[4]) {
    double edges[6];
    double face_areas[4];
    double total_area = 0.0;
    
    edges[0] = calculate_distance(vertices[0], vertices[1]);
    edges[1] = calculate_distance(vertices[0], vertices[2]);
    edges[2] = calculate_distance(vertices[0], vertices[3]);
    edges[3] = calculate_distance(vertices[1], vertices[2]);
    edges[4] = calculate_distance(vertices[1], vertices[3]);
    edges[5] = calculate_distance(vertices[2], vertices[3]);
    
    face_areas[0] = calculate_triangle_area(edges[0], edges[1], edges[3]);
    face_areas[1] = calculate_triangle_area(edges[0], edges[2], edges[4]);
    face_areas[2] = calculate_triangle_area(edges[1], edges[2], edges[5]);
    face_areas[3] = calculate_triangle_area(edges[3], edges[4], edges[5]);
    
    for (int i = 0; i < 4; i++) {
        if (face_areas[i] < 0.0) {
            return -1.0;
        }
        total_area += face_areas[i];
    }
    
    return total_area;
}

int main(void) {
    Point3D vertices[4];
    double surface_area;
    
    printf("Enter coordinates for 4 vertices of the tetrahedron:\n");
    
    for (int i = 0; i < 4; i++) {
        printf("Vertex %d (x y z): ", i + 1);
        if (scanf("%lf %lf %lf", &vertices[i].x, &vertices[i].y, &vertices[i].z) != 3) {
            fprintf(stderr, "Error: Invalid input\n");
            return EXIT_FAILURE;
        }
    }
    
    surface_area = calculate_tetrahedron_surface_area(vertices);
    
    if (surface_area < 0.0) {
        fprintf(stderr, "Error: Invalid tetrahedron geometry\n");
        return EXIT_FAILURE;
    }
    
    printf("Surface area of tetrahedron: %.6f\n", surface_area);
    
    return EXIT_SUCCESS;
}