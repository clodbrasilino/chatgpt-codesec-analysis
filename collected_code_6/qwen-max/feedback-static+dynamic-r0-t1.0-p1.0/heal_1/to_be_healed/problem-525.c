#include <stdio.h>
#include <stdbool.h>

typedef struct {
    double a;
    double b;
    /* Possible weaknesses found:
     *  struct member 'Line::c' is never used. [unusedStructMember]
     */
    double c;
} Line;

bool areLinesParallel(Line line1, Line line2) {
    return (line1.a * line2.b == line2.a * line1.b);
}

int main() {
    Line l1 = {2, 3, 1};
    Line l2 = {4, 6, 2};

    if (areLinesParallel(l1, l2)) {
        printf("The lines are parallel.\n");
    } else {
        printf("The lines are not parallel.\n");
    }

    return 0;
}