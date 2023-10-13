#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
#define BLOCKSIZE 512

int main(int argc, char *argv[])
{ 
    if (argc != 2)
    {
        printf("Usage: ./recover filename.raw\n");
        return 1;
    }
    
    FILE* file = fopen(argv[1], "r"); // Verifying validity of the file
    if (file == NULL)
    {
        printf("Could not open the file %s\n", argv[1]);
        return 1;
    }
    
    FILE *image; // Pointer for the future images
    BYTE buffer[BLOCKSIZE]; // Buffer for storing the data of the file
    char image_name[8];
    int jpgCount = 0;
    
    // While there are archives to recover
    while (fread(buffer, BLOCKSIZE, 1, file) == 1)
    { 
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close the last JPEG, if necessary
            if (jpgCount > 0)
            {
                fclose(image);
            }
            
            // Create the JPEG
            sprintf(image_name, "%03i.jpg", jpgCount);
            image = fopen(image_name, "w");
            if (image == NULL)
            {
                printf("No memory for recovering the card\n");
                return 2;
            }
            fwrite(buffer, sizeof(BYTE), 512, image);
            jpgCount++; // Keeping track of how many JPGs we have
        }
        else if (jpgCount > 0) // If we're after a JPEG file, then keep write
        {
            fwrite(buffer, sizeof(BYTE), 512, image);
        }
    }
}