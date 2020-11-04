#include "libimg.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE (0==0)
#define FALSE (0==1)

#define DEBUG 0

#define NUMBER_OF_THREADS 1

ppm_image image_sobel;
ppm_image res;

const char sobel_x[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
const char sobel_y[3][3] = {{1,2,1},{0,0,0},{-1,-2,-1}};

void *render(void *tid){

    int id = (int)tid;

    int blocksize = ((image_sobel->width)-2)/NUMBER_OF_THREADS;

    //printf("Tam bloco=%d\n", blocksize);
    //printf("Altura=%d\n Largura=%d\n", image_sobel->height-2, image_sobel->width-2);

        for(int y = 1; y <= image_sobel->height-2 ; y++)
    	{
                for(int x = ((id*blocksize) + 1) ; x <= (id+1)*blocksize ; x++)
	        {
                    //printf("Sou a thread n:%d Laço y:%d x:%d\n", id,y,x);
	            unsigned char fa = GET_PIXEL(image_sobel,x-1,y-1)[0];
	            unsigned char fb = GET_PIXEL(image_sobel,x,y-1)[0];
	            unsigned char fc = GET_PIXEL(image_sobel,x+1,y-1)[0];
	            unsigned char fd = GET_PIXEL(image_sobel,x-1,y)[0];
	            unsigned char fe = GET_PIXEL(image_sobel,x,y)[0];
	            unsigned char ff = GET_PIXEL(image_sobel,x+1,y)[0];
	            unsigned char fg = GET_PIXEL(image_sobel,x-1,y+1)[0];
	            unsigned char fh = GET_PIXEL(image_sobel,x,y+1)[0];
	            unsigned char fi = GET_PIXEL(image_sobel,x+1,y+1)[0];

                    short pixel_x = (sobel_x[0][0] * fa ) + (sobel_x[0][1] * fb ) + (sobel_x[0][2] * fc) + (sobel_x[1][0] * fd) + (sobel_x[1][1] * fe) + (sobel_x[1][2] * ff) + (sobel_x[2][0] * fg) + (sobel_x[2][1] * fh) + (sobel_x[2][2] * fi);

                    short pixel_y = (sobel_y[0][0] * fa ) + (sobel_y[0][1] * fb ) + (sobel_y[0][2] * fc) + (sobel_y[1][0] * fd) + (sobel_y[1][1] * fe) + (sobel_y[1][2] * ff) + (sobel_y[2][0] * fg) + (sobel_y[2][1] * fh) + (sobel_y[2][2] * fi);

                    short val = abs(pixel_x) + abs(pixel_y);
	            unsigned char char_val = (255-(unsigned char)(val));

	            if(char_val > 200)
	                char_val = 255;
	            else if(char_val < 100)
	                char_val = 0;

	            //put_pixel_unsafe(img, x,y, (unsigned char) (val), (unsigned char) (val), (unsigned char) (val));
	            //put_pixel_unsafe(img, x,y, ans, ans, ans);
	            put_pixel_unsafe(res, x,y, char_val, char_val, char_val);
	        }
//                printf("y=%d\n",y);
	    }
    pthread_exit(NULL);
}


int main(int argc, char **argv)
{
    printf("Main iniciando\n");

    double time_start = get_time();
    char temp[50];
    strcpy(temp,"");
    if(argc < 3)
    {
        printf("usage: ./sobel <image input file> <image output file>\n");
        return 1;
    }

    printf("input: %s\n",argv[1]);
    printf("output: %s\n",argv[2]);


    FILE *fp = fopen(argv[1],"rb");
    if(fp == NULL) {
        fprintf(stderr,"error, cannot open file %s\n",argv[1]);
        return 1;
    }

    ppm_image image = get_ppm(fp);
    if(image == NULL)
    {
        fprintf(stderr,"error, cannot load image %s\n",argv[1]);
        return 1;
    }
    fclose(fp);

#if DEBUG
    fp = fopen("test.ppm","wb");
    if(fp == NULL)
    {
        fprintf(stderr,"error, cannot open file test.ppm\n");
        return 1;
    }
    output_ppm(fp,image);
    fclose(fp);
#endif

    printf("Executando...\n");

    image_sobel=alloc_img(image->width + 2, image->height + 2);
    //fill_img(image_sobel,0,0,0);

    unsigned int i, j;
    for(i = 0 ; i < image_sobel->width ; i++)
    {
        for(j = 0 ; j < image_sobel->height ; j++)
        {
            if((i == 0) || (i == (image_sobel->width-1)))
            {
                put_pixel_unsafe(image_sobel, i,j, 255,0,0);
            }
            else if((j == 0) || (j == (image_sobel->height-1)))
            {
                put_pixel_unsafe(image_sobel, i,j, 255,0,0);
            }
            else
            {
                put_pixel_unsafe(image_sobel, i,j, GET_PIXEL(image,i-1,j-1)[0], GET_PIXEL(image,i-1,j-1)[1], GET_PIXEL(image,i-1,j-1)[2]);
            }
        }
    }

    to_greyscale(image_sobel);

    res=alloc_img(image_sobel->width, image_sobel->height);

    if(res == NULL)
    {
        fprintf(stderr,"error, cannot allocate sobel image\n");
        return 1;
    }

    //printf("Criação de threads\n");
    double time_sobel_start = get_time();

    pthread_t threads[NUMBER_OF_THREADS];
    int status,t;

    for(t=0;t<NUMBER_OF_THREADS;t++){
        printf("Thread n=%d\n", t);

        status = pthread_create( &threads[t] , NULL , render , (void *)t );

        //printf("Teste\n");
        if(status!=0){
	    printf("pthread_create returned error code %d\n", t);
            exit(-1);
        }
    }

    for(t=0;t<NUMBER_OF_THREADS;t++){
        pthread_join(threads[t], NULL);
    }

    double time_sobel_finish = get_time();

    fp = fopen(argv[2],"wb");
    if(fp == NULL)
    {
        fprintf(stderr,"error, cannot open file %s\n",argv[2]);
        return 1;
    }

    output_ppm(fp,res);
    fclose(fp);
    double time_finish = get_time();
    printf("%f\t| %f\n", time_finish-time_start, time_sobel_finish-time_sobel_start );

    return 0;
}
