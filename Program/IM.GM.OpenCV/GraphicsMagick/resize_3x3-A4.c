//---------------
/* How to build */
/* gcc -o core_dlopen core_dlopen.c `pkg-config --cflags MagickCore` -ldl */
//----------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <dlfcn.h>
#include <magick/api.h>

int main(int argc, char **argv)
{
	ExceptionInfo exception;
	Image *image, *images, *crop_image, *resize_image;
	ImageInfo *image_info;
	RectangleInfo crop_info;

    struct timeval timeBegin, timeStart, timeEnd;
    double runTime = 0;

	gettimeofday(&timeStart, NULL);
    gettimeofday(&timeBegin, NULL);

	//if (argc != 3)
	//{
	// (void) fprintf(stdout,"Usage: %s image thumbnail\n",argv[0]);
	//  exit(0);
	//}

	/*
	Initialize the image info structure and read an image.
	*/
	InitializeMagick(*argv);
	GetExceptionInfo(&exception);
	image_info = CloneImageInfo((ImageInfo*) NULL);
	(void) strcpy(image_info->magick, "RGB");
	image_info->depth = 8;
	CloneString(&(image_info->size), "4725x6780");
	(void) strcpy(image_info->filename, "tiger-A4-4725x6780.rgb");
	images=ReadImage(image_info, &exception);

	if (exception.severity != UndefinedException)
		CatchException(&exception);

	if (images == (Image*) NULL)
		exit(1);

	/*
	Convert the image to a thumbnail
	*/

	image = RemoveFirstImageFromList(&images);
	if (image == (Image*) NULL)
		exit(1);

    /*
	clone_image = fun_CloneImage(image, 0, 0, MagickTrue, exception);
	if (clone_image == (Image*) NULL)
		exit(1);
    
    image = fun_DestroyImage(image);
    */

	crop_info.width = 1574;
	crop_info.height = 2260;   
    (void) strcpy(image_info->magick, "BMP");

    gettimeofday(&timeEnd, NULL);
    runTime = (timeEnd.tv_sec - timeStart.tv_sec) + (double)(timeEnd.tv_usec - timeStart.tv_usec) / 1000000;
    printf("Initialize time is is %lf\n", runTime);

	for (int index = 1; index <=9; index++)
	{
		gettimeofday(&timeStart, NULL);

        switch (index)
		{
		case 1:
			crop_info.x = 0;
			crop_info.y = 0;               
			break;
		case 2:
			crop_info.x = 1574;
			crop_info.y = 0;                
			break;
		case 3:
			crop_info.x = 3149;
			crop_info.y = 0;                
			break;
		case 4:
			crop_info.x = 0;
			crop_info.y = 2260;               
			break;
		case 5:
			crop_info.x = 1574;
			crop_info.y = 2260;
			break;
		case 6:
			crop_info.x = 3149;
			crop_info.y = 2260;
			break;
		case 7:
			crop_info.x = 0;
			crop_info.y = 4520;
			break;
		case 8:
			crop_info.x = 1574;
			crop_info.y = 4520;
			break;
		case 9:
			crop_info.x = 3149;
			crop_info.y = 4520;
			break;		
		default:
			break;
		}

		crop_image = CropImage(image, &crop_info, &exception);
        
        gettimeofday(&timeEnd, NULL);
        runTime = (timeEnd.tv_sec - timeStart.tv_sec) + (double)(timeEnd.tv_usec - timeStart.tv_usec) / 1000000;
        printf("%d crop time is is %lf\n", index, runTime);

        gettimeofday(&timeStart, NULL);

        /*

		if (crop_image != (Image*) NULL)
		{
			(void) sprintf(crop_image->filename, "poster_2x2_A3_crop_%d.bmp", index);
            (void) strcpy(image_info->filename, crop_image->filename);
            (void) strcpy(image_info->magick, "BMP");

			fun_WriteImage(image_info, crop_image);
            fun_DestroyImage(crop_image);

            crop_image=fun_ReadImage(image_info, exception);
        }

        */       
	
        if (crop_image != (Image*) NULL)
        {		
            resize_image = ResizeImage(crop_image, 4725, 6780, LanczosFilter/*TriangleFilter*/, 1.0, &exception);
            if (resize_image != (Image*) NULL)
            {
                (void) sprintf(resize_image->filename, "poster_3x3_A4_%d.bmp", index);
                WriteImage(image_info, resize_image);
			    DestroyImage(resize_image); 
            }
            			     
			DestroyImage(crop_image);			
		}

        gettimeofday(&timeEnd, NULL);
        runTime = (timeEnd.tv_sec - timeStart.tv_sec) + (double)(timeEnd.tv_usec - timeStart.tv_usec) / 1000000;
        printf("%d resize is %lf\n", index, runTime);
	}

	/*
	Destory the image thumbnail and exit
	*/
	DestroyImageInfo(image_info);
	DestroyImage(image);
	DestroyExceptionInfo(&exception);
	DestroyMagick();

    runTime = (timeEnd.tv_sec - timeBegin.tv_sec) + (double)(timeEnd.tv_usec - timeBegin.tv_usec) / 1000000;
    printf("runTime is %lf\n", runTime);

	return(0);    
}