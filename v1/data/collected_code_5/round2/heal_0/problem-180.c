#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846

double degToRad(double deg) {
    return deg * (PI/180);
}

double calculateDistance(double lat1, double long1, double lat2, double long2) {
    double dLat = degToRad(lat2 - lat1);
    double dLong = degToRad(long2 - long1);

    lat1 = degToRad(lat1);
    lat2 = degToRad(lat2);

    double a = sin(dLat/2) * sin(dLat/2) +
                sin(dLong/2) * sin(dLong/2) * cos(lat1) * cos(lat2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double radius = 6371;  // Radius of the earth in km

    return radius * c;
}

int main() {
    double lat1, long1, lat2, long2;

    printf("Enter latitude of first point: ");
    if (scanf("%lf", &lat1) != 1){
        return -1;
    }      

    printf("Enter longitude of first point: ");
    if (scanf("%lf", &long1) != 1){
        return -1;
    }      

    printf("Enter latitude of second point: ");
    if (scanf("%lf", &lat2) != 1){
        return -1;
    } 

    printf("Enter longitude of second point: ");
    if (scanf("%lf", &long2) != 1){
        return -1;
    } 

    double distance = calculateDistance(lat1, long1, lat2, long2);

    printf("Distance between points: %.2lf km\n", distance);

    return 0;
}