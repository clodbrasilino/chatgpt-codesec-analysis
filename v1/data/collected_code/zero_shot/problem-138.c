#include <math.h>

int canBeRepresentedAsSumOfPowersOfTwo(int num) {
    // Base case
    if (num < 0) {
        return 0;
    }
    
    // Checking from highest power of 2 downwards
    int power = (int) log2(num);
    while (power >= 0) {
        int current_power = pow(2, power);
        
        // If the current power can be subtracted from the number,
        // update the number with the difference
        if (num >= current_power) {
            num -= current_power;
            
            // If the updated number is 0, it can be represented
            // as sum of non-zero powers of 2
            if (num == 0) {
                return 1;
            }
        }
        
        // Move to next lower power of 2
        power--;
    }
    
    return 0;
}