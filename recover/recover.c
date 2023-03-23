#include <stdio.h>
#include <stdint.h>

typedef uint8_t byte;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Command format: ./recover <file name>\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");

    if (!card) // Checks if file is available
    {
        printf("File not found\n");
        return 1;
    }

    byte buffer[512]; // Array of 512 bytes
    char filename[8]; // 8 characters of filename

    int i = 0; // To track current name
    FILE *img = NULL; // Initalises image file

    while (fread(buffer, 1, 512, card) == 512) // Loops until fread does not return 512
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) // Checks the first 4 bytes
        {
            if (img != NULL)
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", i); // Makes file
            img = fopen(filename, "w"); // Opens file
            fwrite(buffer, 1, 512, img); // Writes to file
            i++;
        }
        else
        {
            if (img != NULL)
            {
                fwrite(buffer, 1, 512, img); // Write to file if a file is open and the beginning is not a JPEG header
            }
        }
    }

    if (img != NULL)
    {
        fclose(img); // Closes image
    }

    fclose(card); // Closes file

    return 0;
}
