#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'sqrt'
  */

double tetrahedron_volume(double edge_length) {
    /* Possible weaknesses found:
     *  include the header <math.h> or explicitly provide a declaration for 'sqrt'
     *  implicit declaration of function 'sqrt' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'sqrt' with type 'double (double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    return (edge_length * edge_length * edge_length) / (6.0 * sqrt(2.0));
}

int main() {
    double edge = 0.0;
    printf("Enter the edge length of the tetrahedron: ");
    if (scanf("%lf", &edge) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }
    if (edge <= 0) {
        fprintf(stderr, "Edge length must be positive.\n");
        return 1;
    }

    double volume = tetrahedron_volume(edge);
    printf("Volume of the tetrahedron: %f\n", volume);

    return 0;
}