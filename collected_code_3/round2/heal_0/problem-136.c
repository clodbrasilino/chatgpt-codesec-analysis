#include <stdio.h>

float calculateElectricityBill(float units)
{
    float bill_amount;

    if(units <= 50)
    {
        bill_amount = units * 0.50;
    }
    else if(units <= 150)
    {
        bill_amount = 25 + ((units-50) * 0.75);
    }
    else if(units <= 250)
    {
        bill_amount = 100 + ((units-150) * 1.20);
    }
    else
    {
        bill_amount = 220 + ((units-250) * 1.50);
    }

    bill_amount = bill_amount + (bill_amount * 0.20);

    return bill_amount;
}

int main()
{
    float units, bill;

    printf("Enter total units consumed: ");
    scanf("%f", &units);

    bill = calculateElectricityBill(units);

    printf("Electricity Bill = %.2f\n", bill);

    return 0;
}