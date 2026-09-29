#include <stdio.h>
#include <math.h>

int isReciprocal (float a, float b, float c) {
    float root1, root2;
    float discriminant = b*b - 4*a*c;
  
    if (discriminant < 0 || a == 0) {
        return 0;
    }
    
    root1 = (-b + sqrt(discriminant)) / (2*a);
    root2 = (-b - sqrt(discriminant)) / (2*a);

    if (fabs(root1 - (1/root2)) < 0.000001 && fabs(root2 - (1/root1)) < 0.000001) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
   float a, b, c;

   printf("Enter a, b and c of quadratic equation ax^2 + bx + c: ");
   scanf("%f %f %f",&a,&b,&c);

   if (isReciprocal(a, b, c))
     printf("Roots are reciprocal\n");
   else
     printf("Roots are NOT reciprocal\n");

   return 0;
}