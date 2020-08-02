/*
# Course: MP-6171 High Performance Embedded Systems
# Tecnologico de Costa Rica (www.tec.ac.cr)
# Developer Name: Sergio Guillen (guillen_sergio@hotmail.com)
#
# General purpose: RGB to YUB Conversion
#
# Usage:
# ./rgb2yuv [ -i RGBfile ] [ -o YUVfile ] [-h] [-a]
# 
# Inputs: 
#           input file  [-i]: RGBfile specifies the RGB file to be converted
#           output file [-o]: YUVfile specifies the output file name
#                       [-a]: Displays the information of the author of the program.
#                       [-h]: Displays the usage message to let the user know how to execute the application.
#
# Output:
#           Image file converted to YUV*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

unsigned char file_buffer[921600];

void rgb2yuv(char* input_image, char* output_image);
void get_help();

void get_help(){
  printf("Usage\n");
  printf("./rgb2yuv [ -i RGBfile ] [ -o YUVfile ] [-h] [-a]"); 
  printf("-a displays the information of the author of the program.\n");
  printf("-h displays the usage message to let the user know how to");
  printf(" execute the application.\n");
  printf("-i RGBfile specifies the RGB file to be converted.\n");
  printf("-o YUVfile specifies the output file name.\n");
}

int main(int argc, char **argv){
  clock_t t;
  char *input_file = NULL;
  char *output_file = NULL;
  int index;
  int c;
  int input_provided = 0, output_provided = 0;

  opterr = 0;

  if (argc == 1){
    get_help();
    return 0;
  }

  while ((c = getopt(argc, argv, "i:o:")) != -1){
    switch (c){
      case 'a':
        printf("Author: Sergio Guillen (guillen_sergio@hotmail.com)\n");
        return 0;
        break;
      case 'h':
        get_help();
        return 0;
      case 'i':
        input_provided = 1;
        input_file = optarg;
        break;
      case 'o':
        output_provided = 1;
        output_file = optarg;
        break;
      case '?':
        if (optopt == 'i' || optopt == 'o')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
        break;
      default:
        return 0;
    }
  }
  for (index = optind; index < argc; index++){
    printf("Argument %s is not a valid argument, use -h for help \n",
           argv[index]);
  }

  if ((input_provided + output_provided) < 2){
    printf("input and output files must be specified\n");
    printf("Use -h for help \n");
    return 0;
  }

  t=clock();
  rgb2yuv(input_file, output_file);
  t = clock()-t;

  printf("Input RGB file %s converted to output YUV file %s in %f seconds\n",input_file, output_file, (float)t/CLOCKS_PER_SEC);

  return 0;
}

void rgb2yuv(char* input_image, char* output_image){
	unsigned char RGB[3];
	FILE *inputFile, *outputFile;
	inputFile = fopen(input_image,"r");
	outputFile = fopen(output_image,"w");
	int input_count = fread(&file_buffer,sizeof(unsigned char), 921600, inputFile);

	for(int i=0; i<input_count; i+=3) {
		for(int j=0; j<3; j++) RGB[j] = file_buffer[i+j];
		file_buffer[i] = 0.257*RGB[0]+0.504*RGB[1]+0.098*RGB[2]+16;
		file_buffer[i+1] = -0.148*RGB[0]-0.291*RGB[1]+0.439*RGB[2]+128;
		file_buffer[i+2] = 0.439*RGB[0]-0.368*RGB[1]-0.071*RGB[2]+128;
	}
	int output_count = fwrite(file_buffer,sizeof(unsigned char), 921600, outputFile);
	fclose(outputFile);
	fclose(inputFile);
}
