#include <stdio.h>
#include <math.h>

#define PARABOLA_EPSILON 1e-12

typedef struct {
    double x;
    double y;
} Point2D;

typedef enum {
    PARABOLA_OK = 0,
    PARABOLA_ERR_INVALID_COEFF = -1,
    PARABOLA_ERR_INVALID_PTR = -2
} ParabolaStatus;

static ParabolaStatus find_focus_standard_form(double a, double h, double k, Point2D *focus)
{
    double p;

    if (focus == NULL) {
        return PARABOLA_ERR_INVALID_PTR;
    }

    if (fabs(a) < PARABOLA_EPSILON) {
        return PARABOLA_ERR_INVALID_COEFF;
    }

    p = 1.0 / (4.0 * a);

    focus->x = h;
    focus->y = k + p;

    return PARABOLA_OK;
}

static ParabolaStatus find_focus_general_form(double a, double b, double c, Point2D *focus)
{
    double h;
    double k;
    double p;

    if (focus == NULL) {
        return PARABOLA_ERR_INVALID_PTR;
    }

    if (fabs(a) < PARABOLA_EPSILON) {
        return PARABOLA_ERR_INVALID_COEFF;
    }

    h = -b / (2.0 * a);
    k = c - (b * b) / (4.0 * a);
    p = 1.0 / (4.0 * a);

    focus->x = h;
    focus->y = k + p;

    return PARABOLA_OK;
}

static const char *parabola_status_string(ParabolaStatus status)
{
    switch (status) {
        case PARABOLA_OK:
            return "success";
        case PARABOLA_ERR_INVALID_COEFF:
            return "invalid coefficient (a must not be zero)";
        case PARABOLA_ERR_INVALID_PTR:
            return "invalid pointer (NULL)";
        default:
            return "unknown error";
    }
}

int main(void)
{
    Point2D focus;
    ParabolaStatus status;

    double a1 = 0.25;
    double h1 = 2.0;
    double k1 = 3.0;

    double a2 = 1.0;
    double b2 = -4.0;
    double c2 = 7.0;

    status = find_focus_standard_form(a1, h1, k1, &focus);
    if (status == PARABOLA_OK) {
        printf("Standard form: y = %.2f(x - %.2f)^2 + %.2f\n", a1, h1, k1);
        printf("Focus: (%.4f, %.4f)\n\n", focus.x, focus.y);
    } else {
        fprintf(stderr, "Error (standard form): %s\n", parabola_status_string(status));
    }

    status = find_focus_general_form(a2, b2, c2, &focus);
    if (status == PARABOLA_OK) {
        printf("General form: y = %.2fx^2 + %.2fx + %.2f\n", a2, b2, c2);
        printf("Focus: (%.4f, %.4f)\n\n", focus.x, focus.y);
    } else {
        fprintf(stderr, "Error (general form): %s\n", parabola_status_string(status));
    }

    status = find_focus_standard_form(0.0, 1.0, 1.0, &focus);
    if (status != PARABOLA_OK) {
        printf("Edge case (a=0): %s\n", parabola_status_string(status));
    }

    status = find_focus_general_form(1.0, 2.0, 3.0, NULL);
    if (status != PARABOLA_OK) {
        printf("Edge case (NULL pointer): %s\n", parabola_status_string(status));
    }

    return 0;
}