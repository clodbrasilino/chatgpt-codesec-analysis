#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

// define structure to represent Point
typedef struct {
    double x;
    double y;
} Point;

// define structure to represent Triangle
typedef struct {
    Point *p1;
    Point *p2;
    Point *p3;
} Triangle;

// function that creates a Point
Point *createPoint(double x, double y) {
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     */
    Point *p = (Point *) malloc(sizeof(Point));
    if (p == NULL) {
        printf("Error in memory allocation.\n");
        /* Possible weaknesses found:
         *  include '<stdlib.h>' or provide a declaration of 'exit'
         *  incompatible implicit declaration of built-in function 'exit' [-Wbuiltin-declaration-mismatch]
         *  implicit declaration of function 'exit' [-Wimplicit-function-declaration]
         */
        exit(1);
    }
    p->x = x;
    p->y = y;
    return p;
}

// function that creates a Triangle
Triangle *createTriangle(Point *p1, Point *p2, Point *p3) {
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     */
    Triangle *t = (Triangle *) malloc(sizeof(Triangle));
    if (t == NULL) {
        printf("Error in memory allocation.\n");
        /* Possible weaknesses found:
         *  incompatible implicit declaration of built-in function 'exit' [-Wbuiltin-declaration-mismatch]
         *  include '<stdlib.h>' or provide a declaration of 'exit'
         */
        exit(1);
    }
    t->p1 = p1;
    t->p2 = p2;
    t->p3 = p3;
    return t;
}

// function that deletes a Point
void deletePoint(Point *p) {
    if (p == NULL) {
        printf("Error: cannot delete null pointer.\n");
        /* Possible weaknesses found:
         *  incompatible implicit declaration of built-in function 'exit' [-Wbuiltin-declaration-mismatch]
         *  include '<stdlib.h>' or provide a declaration of 'exit'
         */
        exit(1);
    }
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     */
    free(p);
}

// function that deletes a Triangle
void deleteTriangle(Triangle *t) {
    if (t == NULL) {
        printf("Error: cannot delete null pointer.\n");
        /* Possible weaknesses found:
         *  incompatible implicit declaration of built-in function 'exit' [-Wbuiltin-declaration-mismatch]
         *  include '<stdlib.h>' or provide a declaration of 'exit'
         */
        exit(1);
    }
    deletePoint(t->p1);
    deletePoint(t->p2);
    deletePoint(t->p3);
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     */
    free(t);
}

// function to calculate distance between two points
double distance(Point *p1, Point *p2) {
    return sqrt(pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2));
}

// function to calculate triangle area
double triangleArea(Triangle *t) {
    double a = distance(t->p1, t->p2);
    double b = distance(t->p2, t->p3);
    double c = distance(t->p3, t->p1);
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

// function to find the largest inscribed triangle
Triangle *findLargestInscribedTriangle(double a, double b) {
    double x = a / sqrt(2);
    double y = b / sqrt(2);
    Point *p1 = createPoint(x, y);
    Point *p2 = createPoint(-x, -y);
    Point *p3 = createPoint(-x, y);
    return createTriangle(p1, p2, p3);
}

int main() {
    double a = 5.0;
    double b = 3.0;
    Triangle *t = findLargestInscribedTriangle(a, b);
    double area = triangleArea(t);
    printf("The area of the largest inscribed triangle is: %.2f\n", area);
    deleteTriangle(t);
    return 0;
}