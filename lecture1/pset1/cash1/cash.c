#include <cs50.h> 
#include <stdio.h>
#include <math.h>

int main(void)
{
    float change;
    int coins = 0;
    int cents = 0;
    int qrt = 25;
    int dm = 10; 
    int nckl = 5; 
    int pnn = 1;
    
    // Asking for the change owed:
    do 
    {
        change = round(get_float("Change owed: ") * 100);
    } while (change < 1);
    
    // Calculating how many coins it needs:
    while (cents + qrt <= change) 
    {
        coins++;
        cents += qrt; 
    } 
    
    while (cents + dm <= change) 
    {
        coins++;
        cents += dm;
    } 
    
    while (cents + nckl <= change)
    {
        coins++;
        cents += nckl;
    }
    
    while (cents + pnn <= change)
    {
        coins++;
        cents += pnn;
    }
    
    // Just printing how many coins:
    printf("%i\n", coins);
}