#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <arm_neon.h>

void print_information (void);
void print_author (void);
void argumentParser (int argc, char **argv);
void rgb2yuv (char *input_image, char *output_image);

char *cvalue = NULL;
char *rgbFile = NULL;
char *yuvFile = NULL;

struct timeval start, end;
double t;

/* */
int main (int argc, char **argv)
{
    int c;

    while ((c = getopt (argc, argv, "ahi:o:")) != -1)
    {
        switch (c)
        {
            case 'a':
                print_author();
            break;
            case 'h':
                print_information();
            break;
            case 'o':
                yuvFile = optarg;
            break;
            case 'i':
                rgbFile = optarg;
            break;                                    
            default:
                printf ("Error, no parameters found!!");
            break;
        }
    }

    // get start time to init "profiler"
    gettimeofday(&start, NULL);

    if ((rgbFile != NULL) && (yuvFile != NULL))
    {
       rgb2yuv(rgbFile, yuvFile);
    }

    // get end time
    gettimeofday(&end, NULL);
    t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)) / 1000000.0;

    printf("\n-> Execution time: %f\n\n",t);
}

/* */
void print_information()
{
   printf("\n");
    printf("*************************************************\n");
    printf("This software allows to convert images RGB in YUV format");
    printf("The functionality is detailed as follows:\n");
    printf("If you need read and processing an image you apply in console ./rgb2yuv_openmp [-i RGB input_image] [-o YUV output_image]");
    printf("If you need know the information authors, apply in console ./rgb2yuv_openmp -a\n");
    printf("If you need know information about functionally software, apply in console ./rgb2yuv_openmp -h\n");
    printf("Contact us in email: sercr0388@gmail.com\n");
    printf("*************************************************\n");
}

/* */
void print_author()
{
    printf("\n");
    printf("*************************************************\n");
    printf("Copyright (C) 2020\n");
    printf("Author : Eng.Sergio Arriola-Valverde\n");
    printf("Lecturer in Instituto Tecnologico de Costa Rica\n");
    printf("Email: sercr0388@gmail.com\n");
    printf("\n");
    printf("*************************************************");
    printf("\n");
}

/* */

void rgb2yuv(char *input_image, char *output_image)
{
    FILE *ptr;
    FILE *write_ptr;

    printf("In file: %s\n", input_image);
    printf("Out file: %s\n", output_image);

    int heigth = 640;
    int width = 480;

    int n_bytes = heigth * width * 3;
    int n_pixels = heigth * width;

    unsigned char buffer_in[n_bytes];
    signed char buffer_out[n_bytes];

    // read input RGB file
    ptr = fopen(input_image,"rb");
    fread(buffer_in,n_bytes,1,ptr);

    // rgb_x3x16_tmp.val[0] -> R
    // rgb_x3x16_tmp.val[1] -> G
    // rgb_x3x16_tmp.val[2] -> B
    uint8x16x3_t rgb_x3x16_tmp;

    // yuv_x3x16_tmp.val[0] -> Y
    // yuv_x3x16_tmp.val[1] -> U
    // yuv_x3x16_tmp.val[2] -> V
    uint8x16x3_t yuv_x3x16_tmp;

    // pointer to input RGB image
    uint8_t *rgb_ptr = buffer_in;
    uint8_t *yuv_ptr = buffer_out;

    if (ptr != NULL)
    {
        // Input format: RGB24, low memory-->|B G R|B G R|B G R|....|B G R|B G R|B G R|<--high memory
        // Output format: YUV444 packed, low memory->|Y U V |Y U V|....||Y U V..|Y U V..|<--high memory
        
        // get YUV components
        for(int i = 0; i<n_pixels/16; i++)
        {
            //   YUV 4:4:4 Planar
            /*
            buffer_out[i] = (( buffer_in[(i*3)]*66  + buffer_in[(i*3)+1]* 129 + buffer_in[(i*3)+2]*25   + 128) >> 8) + 16;      
            buffer_out[n_pixels+i] = ((-buffer_in[(i*3)]*38  - buffer_in[(i*3)+1]* 74  + buffer_in[(i*3)+2]*112  + 128) >> 8) + 128;     
            buffer_out[2*n_pixels+i] = (( buffer_in[(i*3)]*112 - buffer_in[(i*3)+1]* 94  - buffer_in[(i*3)+2]*18   + 128) >> 8) + 128;
            */  

            // get rgb for next 16 pixels
            rgb_x3x16_tmp = vld3q_u8(rgb_ptr+i*16*3);

            // get RGB high and low vector sectors in 16bit uints (needed to handle multiplications)
            uint8x8_t high_r = vget_high_u8(rgb_x3x16_tmp.val[2]);
            uint8x8_t low_r = vget_low_u8(rgb_x3x16_tmp.val[2]);
            uint8x8_t high_g = vget_high_u8(rgb_x3x16_tmp.val[1]);
            uint8x8_t low_g = vget_low_u8(rgb_x3x16_tmp.val[1]);
            uint8x8_t high_b = vget_high_u8(rgb_x3x16_tmp.val[0]);
            uint8x8_t low_b = vget_low_u8(rgb_x3x16_tmp.val[0]);

            int16x8_t signed_high_r = vreinterpretq_s16_u16(vaddl_u8(high_r, vdup_n_u8(0)));
            int16x8_t signed_low_r = vreinterpretq_s16_u16(vaddl_u8(low_r, vdup_n_u8(0)));
            int16x8_t signed_high_g = vreinterpretq_s16_u16(vaddl_u8(high_g, vdup_n_u8(0)));
            int16x8_t signed_low_g = vreinterpretq_s16_u16(vaddl_u8(low_g, vdup_n_u8(0)));
            int16x8_t signed_high_b = vreinterpretq_s16_u16(vaddl_u8(high_b, vdup_n_u8(0)));
            int16x8_t signed_low_b = vreinterpretq_s16_u16(vaddl_u8(low_b, vdup_n_u8(0)));

            // coeficients for Y
            uint8x8_t coef1 = vdup_n_u8(66);
            uint8x8_t coef2 = vdup_n_u8(129);
            uint8x8_t coef3 = vdup_n_u8(25);

            // compute Y
            uint16x8_t high_y = vmull_u8(high_r, coef1);
            high_y = vmlal_u8(high_y, high_g, coef2);
            high_y = vmlal_u8(high_y, high_b, coef3);
            uint16x8_t low_y  = vmull_u8(low_r, coef1);
            low_y = vmlal_u8(low_y, low_g, coef2);
            low_y = vmlal_u8(low_y, low_b, coef3);

            high_y = vaddq_u16(high_y, vdupq_n_u16(128));
            low_y = vaddq_u16(low_y, vdupq_n_u16(128));

            uint8x16_t y = vcombine_u8(vqshrn_n_u16(low_y, 8), vqshrn_n_u16(high_y, 8));
            yuv_x3x16_tmp.val[0] = y;

            // coeficients for U
            int16x8_t scoef1 = vdupq_n_s16(112);
            int16x8_t scoef2 = vdupq_n_s16(-94);
            int16x8_t scoef3 = vdupq_n_s16(-18);

            // compute U
            int16x8_t high_u = vmulq_s16(signed_high_r, scoef1);
            high_u = vmlaq_s16(high_u, signed_high_g, scoef2);
            high_u = vmlaq_s16(high_u, signed_high_b, scoef3);
            int16x8_t low_u = vmulq_s16(signed_low_r, scoef1);
            low_u = vmlaq_s16(low_u, signed_low_g, scoef2);
            low_u = vmlaq_s16(low_u, signed_low_b, scoef3);

            high_u = vaddq_s16(high_u, vdupq_n_s16(128));
            low_u = vaddq_s16(low_u, vdupq_n_s16(128));

            int8x16_t u = vcombine_s8(vqshrn_n_s16(low_u, 8), vqshrn_n_s16(high_u, 8));
            u = vaddq_s8(u, vdupq_n_s8(128));
            yuv_x3x16_tmp.val[1] = vreinterpretq_u8_s8(u);

            // coeficients for V
            scoef1 = vdupq_n_s16(-38);
            scoef2 = vdupq_n_s16(-74);
            scoef3 = vdupq_n_s16(112);

            // compute V
            int16x8_t high_v = vmulq_s16(signed_high_r, scoef1);
            high_v = vmlaq_s16(high_v, signed_high_g, scoef2);
            high_v = vmlaq_s16(high_v, signed_high_b, scoef3);
            int16x8_t low_v = vmulq_s16(signed_low_r, scoef1);
            low_v = vmlaq_s16(low_v, signed_low_g, scoef2);
            low_v = vmlaq_s16(low_v, signed_low_b, scoef3);

            high_v = vaddq_s16(high_v, vdupq_n_s16(128));
            low_v = vaddq_s16(low_v, vdupq_n_s16(128));

            int8x16_t v = vcombine_s8(vqshrn_n_s16(low_v, 8), vqshrn_n_s16(high_v, 8));
            v = vaddq_s8(v, vdupq_n_s8(128));
            yuv_x3x16_tmp.val[2] = vreinterpretq_u8_s8(v);;

            // store
            vst3q_u8(yuv_ptr, yuv_x3x16_tmp);
            yuv_ptr += 3*16;
        }
    }

    write_ptr = fopen(output_image,"wb");
    fwrite(buffer_out,n_bytes,1,write_ptr);    

    fclose(ptr);
    fclose(write_ptr);
}

