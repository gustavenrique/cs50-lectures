#include <cs50.h>
#include <stdio.h>

float average(int how_many, int value[]);

int main(void)
{
    //how many numbers:
    const int q = get_int("How many numbers: ");
    
    //ask for and add them to the array of numbers:
    int numbers[q];
    
    for (int i = 0; i < q; i++)
    {
        numbers[i] = get_int("Number %i: ", i + 1);
    }

    //to calculate display the average:
    printf("Average: %.2f\n", average(q, numbers));
    
}

// average function:
    float average(int how_many, int value[])
    {
        int sum = 0;
        
        for (int i = 0; i < how_many; i++)
        {
            sum += value[i];
        }
        return sum / (float) how_many;
    }
    