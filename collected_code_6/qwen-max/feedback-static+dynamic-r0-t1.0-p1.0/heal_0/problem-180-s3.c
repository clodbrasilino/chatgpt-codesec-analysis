#include <stdio.h>
#include <math.h>

double calculate_distance(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6371.0; 
    double lat_rad1 = lat1 * M_PI / 180.0;
    double lat_rad2 = lat2 * M_PI / 180.0;
    double delta_lat = (lat2 - lat1) * M_PI / 180.0;
    double delta_lon = (lon2 - lon1) * M_PI / 180.0;

    double a = sin(delta_lat / 2) * sin(delta_lat / 2) +
               cos(lat_rad1) * cos(lat_rad2) *
               sin(delta_lon / 2) * sin(delta_lon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    
    return R * c;
}

int main() {
    double lat1, lon1, lat2, lon2;
    
    printf("Enter the latitude and longitude of the first point: ");
    scanf("%lf %lf", &lat1, &lon1);
    
    printf("Enter the latitude and longitude of the second point: ");
    scanf("%lf %lf", &lat2, &lon2);
    
    double distance = calculate_distance(lat1, lon1, lat2, lon2);
    
    printf("Distance between the two points: %.2f km\n", distance);
    
    return 0;
}