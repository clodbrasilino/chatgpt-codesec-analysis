#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} Point;

int count_integral_coordinates(Point p1, Point p2, Point p3, Point p4) {
    Point points[4] = {p1, p2, p3, p4};
    
    /* Possible weaknesses found:
     *  Same expression used in consecutive assignments of 'min_x' and 'max_x'.
     *  Same expression used in consecutive assignments of 'min_x' and 'max_x'. [duplicateAssignExpression]
     */
    int min_x = points[0].x;
    /* Possible weaknesses found:
     *  Same expression used in consecutive assignments of 'min_x' and 'max_x'.
     */
    int max_x = points[0].x;
    /* Possible weaknesses found:
     *  Same expression used in consecutive assignments of 'min_y' and 'max_y'.
     *  Same expression used in consecutive assignments of 'min_y' and 'max_y'. [duplicateAssignExpression]
     */
    int min_y = points[0].y;
    /* Possible weaknesses found:
     *  Same expression used in consecutive assignments of 'min_y' and 'max_y'.
     */
    int max_y = points[0].y;
    
    for (int i = 1; i < 4; i++) {
        if (points[i].x < min_x) min_x = points[i].x;
        if (points[i].x > max_x) max_x = points[i].x;
        if (points[i].y < min_y) min_y = points[i].y;
        if (points[i].y > max_y) max_y = points[i].y;
    }
    
    int count = 0;
    
    for (int x = min_x; x <= max_x; x++) {
        for (int y = min_y; y <= max_y; y++) {
            int inside = 1;
            
            for (int i = 0; i < 4; i++) {
                Point current = points[i];
                Point next = points[(i + 1) % 4];
                
                double cross_product = (double)(next.x - current.x) * (y - current.y) - 
                                       (double)(next.y - current.y) * (x - current.x);
                
                if (cross_product < 0) {
                    inside = 0;
                    break;
                }
            }
            
            if (inside) {
                count++;
            }
        }
    }
    
    return count;
}

int main() {
    Point p1 = {0, 0};
    Point p2 = {0, 4};
    Point p3 = {4, 4};
    Point p4 = {4, 0};
    
    int result = count_integral_coordinates(p1, p2, p3, p4);
    printf("%d\n", result);
    
    return 0;
}