#include <stdio.h>
#include <cs50.h>

int main(void) 
{
    // Variable height:
    int h;
    
    // Getting the height from the user:
    do 
    {
        h = get_int("Height: ");
         
        if (h < 1 || h > 8)
        {
             printf("It must be some number between 1 and 8.\n");
        }
    } while (h < 1 || h > 8);
     
    // Creating the brick tower itself 
    
    // i: layer which the brick is on. It keeps increasing 'til the limit height  
    for (int i = 1; i <= h; i++) {
        
        // s: space required to let the brick tower to the right 
        for (int s = h - i; s > 0; s--) {
            printf(" ");
        }
        
        // j: how many blocks in the given layer
        for (int j = 1; j <= i; j++) {
            printf("#");
        }
        printf("\n");
    }
    
}