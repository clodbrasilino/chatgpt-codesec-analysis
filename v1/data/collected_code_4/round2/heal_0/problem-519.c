#include <stdio.h>
#include <math.h>

double calculate_volume(double edge_length) {
    if(edge_length <= 0)
        return -1;

    double volume = pow(edge_length, 3) / (6 * sqrt(2));

    return volume;
}

int main() {
    double edge_length;
    printf("Enter the edge length of the Tetrahedron: ");
    scanf("%lf", &edge_length);
    
    double volume = calculate_volume(edge_length);

    if(volume == -1) {
        printf("Invalid input. Edge length should be positive.\n");
        return -1;
    } 

    printf("Volume of the Tetrahedron with edge length %.2f is: %.2f\n", edge_length, volume);
 
    return 0;
}