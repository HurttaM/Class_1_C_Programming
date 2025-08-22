#include <stdio.h>

/*
Write a program that defines two floating-point arrays of 12 elements each. The program then asks
user to enter tax percentage and yearly income limit up to which the percentage applies to and the
(greater) tax percentage that will be applied to income that is over the limit. Then program asks user
to enter salary of each month and stores the values in the array. After user has entered all monthly
salaries, the program calculates tax for each month.
The program prints all salaries with two decimal precision and the amount of tax for each month.
*/


int main(void)
{
    const int MONTHS = 12;
    double wages[MONTHS];
    double taxes[MONTHS];

    double lower_rate;
    double higher_rate;
    double yearly_limit;

    printf("Enter tax rate as a percentage (0-100):\n");
    scanf("%lf", &lower_rate);
    printf("Enter tax rate for income over the limit as a percentage (0-100):\n");
    scanf("%lf", &higher_rate);
    printf("Enter income limit:\n");
    scanf("%lf", &yearly_limit);


    //for loop to ask for each month's salary
    for (int i = 0; i < MONTHS; i++)
    {
        printf("Enter salary for month %d:\n", i + 1);
        scanf("%lf", &wages[i]);
    }

    double remaining_limit = yearly_limit;
    double low_part; //For calculating the parts that are under the remaining yearly limit
    double high_part; //For calculating the parts that go over the remaining yearly limit

//Making sure I have the correct fractions for calculations eg instead of 20 I have 0.2
    higher_rate = higher_rate / 100;
    lower_rate = lower_rate / 100;

    //for loop to calculate each month's taxes
    for (int i = 0; i < MONTHS; i++)
    {
        if (wages[i] < remaining_limit) //if wages are lower than the remaining limit then use lower tax bracket
        {
            low_part = wages[i];
            high_part = 0;
        }
        else //if not then use lower for the amount that doesn't go over and for the rest use higher tax bracket
        {
            low_part = remaining_limit;
            high_part = wages[i] - remaining_limit; //take out any remaining limit if applicable
        }

        taxes[i] = low_part * lower_rate + high_part * higher_rate; //add the taxes together for the month and put into an array
        remaining_limit -= low_part; //substract the amount that didn't go over the remaining limit
    }

    double total_income = 0;
    double total_tax = 0;

    printf("%-5s %12s %12s\n", "Month", "Income", "Tax");
    for (int i = 0; i < MONTHS; i++)
    {
        printf("%-5d %12.2f %12.2f\n", i+1, wages[i], taxes[i]);
        total_income += wages[i];
        total_tax += taxes[i];
    }
    printf("%-5s %12.2f %12.2f\n", "Total", total_income, total_tax);

}