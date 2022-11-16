#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // check number of command line arguments
    if ((argc < 2) || (argc > 2))
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // open the memory card
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // allocate MEMORY for filename
    char *fname = malloc(strlen("###.jpg") + 1);

    // initialize counter for file name
    int fname_counter = 0;

    sprintf(fname, "%03i.jpg", fname_counter);

    // TEST printing the file name
    printf("%s\n", fname);

    // initialize a buffer of 512 bytes
    uint8_t buffer[512];

    // initialize a variable for the block size
    int BLOCK_SIZE = 512;

    // start loop to read in data
    // read in data from the memory card
    while (fread(buffer, 1, BLOCK_SIZE, f) == BLOCK_SIZE)
    {
        // check if 512 byte chunk includes the starting bytes of a jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) // if start of jpg
        {
            printf("Start of JPG\n");
            if (fname_counter == 0) // if first jpg
            {
                printf("fname_counter == 0, Opening %s\n", fname);
                FILE *img = fopen(fname, "w");
                if (img == NULL)
                {
                    printf("Could not open %s.\n", fname);
                    return 1;
                }
                fwrite(buffer, sizeof(uint8_t), BLOCK_SIZE, img);
                fclose(img);
                fname_counter += 1;
            }
            else // not first jpg
            {
                sprintf(fname, "%03i.jpg", fname_counter);
                printf("fname_counter != 0, Opening %s\n", fname);
                FILE *img = fopen(fname, "w");
                if (img == NULL)
                {
                    printf("Could not open %s.\n", fname);
                    return 1;
                }
                fwrite(buffer, sizeof(uint8_t), BLOCK_SIZE, img);
                fclose(img);

                fname_counter += 1;
            }
        }
        else
        {
            if (fname_counter > 0)
            {
                FILE *img = fopen(fname, "a");
                if (img == NULL)
                {
                    printf("Could not open %s.\n", fname);
                    return 1;
                }
                fwrite(buffer, sizeof(uint8_t), BLOCK_SIZE, img);
                fclose(img);
            }
            else
            {
                continue;
            }
        }
    }
    free(fname);
    // fclose(img);
    fclose(f);

}
//     // PSEUDOCODE
//     // open memory card
//     // repeat until end of card
//     // read 512 bytes into a buffer
//         // if start of new jpeg
//             // if first jpeg
//                 // WRITE VERY FIRST FILE
//             // else
//                 // close file you've been writing to
//                 // open up new file to store this new jpg
//         // else
//             // if you've already found a jpg, keep writing to it, it's
//             // just the next bit of data for this image
//     // close any remaining files



//     // READ DATA FROM THE MEMORY CARD
//     fread(data, size, number, inptr);
//     // data: pointer to where to store data you're reading (some buffer / array)
//     // size: number of bytes of each element you're going to try to read
//     // number: number of elements
//     // inptr: FILE * to read from
//     // returns the number of items of size size that were read.

//     // WRITE DATA TO A FILE
//     fwrite(data, size, number, outptr);
//     // data: pointer to all of the bytes that you want to write to the file
//     // size: size of each element, in number of bytes, that you're going to write to the file
//     // number: number of elements to write
//     // outptr: FILE * to write to (file pointer)
