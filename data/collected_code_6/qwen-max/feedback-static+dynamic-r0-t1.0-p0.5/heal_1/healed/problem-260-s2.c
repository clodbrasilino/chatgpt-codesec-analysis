#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool is_prime(long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

long ns_williams(long n) {
    long a = 1, b = 1, c = 1, d = 1, e = 1, f = 1, g = 1, h = 1;
    long count = 0;
    while (true) {
        long P = (a * d - b * c);
        if (P > 1 && is_prime(P)) {
            count++;
            if (count == n) return P;
        }
        long temp_a = a, temp_b = b, temp_c = c, temp_d = d, temp_e = e, temp_f = f, temp_g = g, temp_h = h;
        if (P == 0) P = 1;
        a = (temp_a * temp_e + temp_b * temp_f) % P;
        b = (temp_a * temp_f + temp_b * (temp_e + temp_f)) % P;
        c = (temp_c * temp_e + temp_d * temp_f) % P;
        d = (temp_c * temp_f + temp_d * (temp_e + temp_f)) % P;
        e = (temp_e * temp_g + temp_f * temp_h) % P;
        f = (temp_e * temp_h + temp_f * (temp_g + temp_h)) % P;
        g = (temp_g * temp_g + temp_h * temp_h) % P;
        h = (temp_g * temp_h + temp_h * (temp_g + temp_h)) % P;
    }
}

int main() {
    long n;
    printf("Enter the nth Newman–Shanks–Williams prime number to find: ");
    scanf("%ld", &n);
    long result = ns_williams(n);
    printf("The %ldth Newman–Shanks–Williams prime number is: %ld\n", n, result);
    return 0;
}