#include<stdio.h>
#include<math.h>

int countRectInCircle(int radius){
    int diameter = 2 * radius;
    int recCount = 0;
    for (int length = 1; length <= diameter; ++length){
        for (int width = 1; width <= length; ++width){
            if (sqrt(length * length + width * width) <= diameter){
                ++recCount;
            }
        }
    }
    return recCount;
}

int main(){
    int radius;
    printf("Enter radius of the circle: ");
    scanf("%d", &radius);
    int numberOfRect = countRectInCircle(radius);
    printf("Number of possible rectangles: %d\n", numberOfRect);
    return 0;
}