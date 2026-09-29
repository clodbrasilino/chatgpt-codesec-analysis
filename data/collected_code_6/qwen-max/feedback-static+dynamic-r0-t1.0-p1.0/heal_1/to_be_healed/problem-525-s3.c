#include <stdio.h>
#include <stdbool.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'Line::c' is never used. [unusedStructMember]
     */
    float a, b, c;
} Line;

bool areLinesParallel(Line l1, Line l2) {
    return (l1.a * l2.b == l1.b * l2.a);
}

int main() {
    Line line1 = {2.0, 3.0, -5.0};
    Line line2 = {4.0, 6.0, -10.0};
    
    if (areLinesParallel(line1, line2)) {
        printf("The lines are parallel.\n");
    } else {
        printf("The lines are not parallel.\n");
    }
    
    return 0;
}