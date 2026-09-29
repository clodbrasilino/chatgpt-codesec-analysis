#include <stdio.h>

float calculate_Bill(float units){
    float total;

    if(units<0){
        printf("Error: Units can't be less than 0\n");
        return -1;
    }

    if(units<=50){
        total=units*0.50;
    }
    else if(units<=150){
        total=25+((units-50)*0.75);
    }
    else if(units<=250){
        total=100+((units-150)*1.20);
    }
    else{
        total=220+((units-250)*1.50);
    }

    total=total+(total*0.20);

    return total;
}

int main() {
    float units;
    printf("Enter total units consumed: ");
    if(scanf("%f",&units)!=1){
        printf("Error: Not a number\n");
        return -1;
    }

    float total = calculate_Bill(units);

    if (total != -1) {
        printf("Total Electricity bill is: %.2f \n",total);
    }

    return 0;
}