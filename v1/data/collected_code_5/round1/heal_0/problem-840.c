#include<stdio.h>
#include<math.h>

int checkRoots(double a, double b, double c) {
    double dis = b*b - 4*a*c;
    if(dis < 0)
        return 0;
    
    double root1 = (-b + sqrt(dis)) / (2*a);
    double root2 = (-b - sqrt(dis)) / (2*a);

    if(root1 + root2 == 0)
        return 1;
    else
        return 0;
}

int main() {
    double a, b, c;
    a = 1;
    b = 0;
    c = -1;
    if(checkRoots(a, b, c))
        printf("Roots are numerically equal but opposite in sign\n");
    else
        printf("Roots are not numerically equal but opposite in sign\n");

    return 0;
}