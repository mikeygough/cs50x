// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    // first create an array of 44 bytes in memory to store the WAV file header... also called a buffer
    uint8_t header[HEADER_SIZE];

    // now read that buffer from the input file
    // read 'HEADER_SIZE' bytes from the 'input' file into the 'header' variable
    // remember that the name of an array is the same as a pointer to the first element of the array
    fread(header, HEADER_SIZE, 1, input);

    // after reading that data into memory, write it to the output file
    // write the contents of 'header', to the 'output' file. writing 'HEADER_SIZE' bytes.
    fwrite(header, HEADER_SIZE, 1, output);

    // TODO: Read samples from input file and write updated data to output file
    // For each of those 2 byte samples, read them into memory, modify them, and write to the output file
    // start by creating another buffer which just needs to store enough data for a 2 byte sample
    int16_t buffer; // this type stores an integer of 16 bits (2 bytes)
    // notice that we're not using an array here, literally just 2 bytes.

    // read from the input file, into the buffer (address of the buffer), one sample (2 bytes) at a time
    // this is going to continously ready 2 bytes at a time until the end of the file
    // at the end of the file, fread will return 0 which will break us out of the while loop
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        // Update volume
        buffer *= factor;
        // write data from the buffer, to the output file, 2 bytes at a time.
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);
}