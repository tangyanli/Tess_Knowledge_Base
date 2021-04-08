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
#include <magick/MagickCore.h>

int main(int argc, char **argv)
{
	ExceptionInfo *exception;
	Image *image, *images, *crop_image, *resize_image;
	ImageInfo *image_info;
	RectangleInfo crop_info;

    struct timeval timeBegin, timeStart, timeEnd;
    double runTime = 0;

	void *hLib = NULL;
	void (*fun_MagickCoreGenesis)(const char *,const MagickBooleanType) = NULL;
	ExceptionInfo* (*fun_AcquireExceptionInfo)(void) = NULL;
	ImageInfo* (*fun_CloneImageInfo)(const ImageInfo *) = NULL;
	char* (*fun_CloneString)(char **,const char *) = NULL;
	Image* (*fun_ReadImage)(const ImageInfo *,ExceptionInfo *) = NULL;
	void (*fun_CatchException)(ExceptionInfo *) = NULL;
	Image* (*fun_NewImageList)(void) = NULL;
	Image* (*fun_RemoveFirstImageFromList)(Image **) = NULL;
	Image* (*fun_ResizeImage)(const Image *,const size_t,const size_t,const FilterTypes, const double,ExceptionInfo *) = NULL;
	void (*fun_MagickError)(const ExceptionType,const char *,const char *) = NULL;
	void (*fun_AppendImageToList)(Image **,const Image *) = NULL;
	Image* (*fun_DestroyImage)(Image *) = NULL;
	MagickBooleanType (*fun_WriteImage)(const ImageInfo *,Image *) = NULL;
	Image* (*fun_DestroyImageList)(Image *) = NULL;
	ImageInfo* (*fun_DestroyImageInfo)(ImageInfo *) = NULL;
	ExceptionInfo* (*fun_DestroyExceptionInfo)(ExceptionInfo *) = NULL;
	Image* (*fun_CropImage)(const Image *,const RectangleInfo *,ExceptionInfo *) = NULL;
	Image* (*fun_CloneImage)(const Image *,const size_t,const size_t,const MagickBooleanType, ExceptionInfo *) = NULL;
	void (*fun_MagickCoreTerminus)(void);

    gettimeofday(&timeStart, NULL);
    gettimeofday(&timeBegin, NULL);

	//if (argc != 3)
	//{
	// (void) fprintf(stdout,"Usage: %s image thumbnail\n",argv[0]);
	//  exit(0);
	//}

	// Open library libMagickCore-6.Q16.so.6
	hLib = dlopen("libMagickCore-6.Q16.so.6", RTLD_NOW);
	if (hLib == NULL)
	{
		// If library libMagickCore-6.Q16.so.6 is not existent, then open libMagickCore-6.Q16.so.2
		hLib = dlopen("libMagickCore-6.Q16.so.2", RTLD_NOW);
	}

	if (hLib == NULL)
	{
		(void) fprintf(stdout,"No libMagickCore-6.Q16.so.6 or libMagickCore-6.Q16.so.2\n");
		exit(0);
	}

	fun_MagickCoreGenesis = dlsym(hLib, "MagickCoreGenesis");
	fun_AcquireExceptionInfo = dlsym(hLib, "AcquireExceptionInfo");
	fun_CloneImageInfo = dlsym(hLib, "CloneImageInfo");
	fun_CloneString = dlsym(hLib, "CloneString");
	fun_ReadImage = dlsym(hLib, "ReadImage");
	fun_CatchException = dlsym(hLib, "CatchException");
	fun_NewImageList = dlsym(hLib, "NewImageList");
	fun_RemoveFirstImageFromList = dlsym(hLib, "RemoveFirstImageFromList");
	fun_ResizeImage = dlsym(hLib, "ResizeImage");
	fun_MagickError = dlsym(hLib, "MagickError");
	fun_AppendImageToList = dlsym(hLib, "AppendImageToList");
	fun_DestroyImage = dlsym(hLib, "DestroyImage");
	fun_WriteImage = dlsym(hLib, "WriteImage");
	fun_DestroyImageList = dlsym(hLib, "DestroyImageList");
	fun_DestroyImageInfo = dlsym(hLib, "DestroyImageInfo");
	fun_DestroyExceptionInfo = dlsym(hLib, "DestroyExceptionInfo");
	fun_CropImage = dlsym(hLib, "CropImage");
	fun_CloneImage = dlsym(hLib, "CloneImage");
	fun_MagickCoreTerminus = dlsym(hLib, "MagickCoreTerminus");

	if (fun_MagickCoreGenesis == NULL ||
		fun_AcquireExceptionInfo == NULL ||
		fun_CloneImageInfo == NULL || 
		fun_CloneString == NULL ||
		fun_ReadImage == NULL ||
		fun_CatchException == NULL ||
		fun_NewImageList == NULL ||
		fun_RemoveFirstImageFromList == NULL ||
		fun_ResizeImage == NULL ||
		fun_MagickError == NULL ||
		fun_AppendImageToList == NULL ||
		fun_DestroyImage == NULL ||
		fun_WriteImage == NULL ||
		fun_DestroyImageList == NULL ||
		fun_DestroyImageInfo == NULL ||
		fun_DestroyExceptionInfo == NULL ||
		fun_CropImage == NULL ||
		fun_CloneImage == NULL ||
		fun_MagickCoreTerminus == NULL)
	{
		dlclose(hLib);
		hLib = NULL;
		(void) fprintf(stdout,"Function is null\n");
		exit(0);
	}

	/*
	Initialize the image info structure and read an image.
	*/
	fun_MagickCoreGenesis(*argv, MagickTrue);
	exception = fun_AcquireExceptionInfo();
	image_info = fun_CloneImageInfo((ImageInfo*) NULL);
	(void) strcpy(image_info->magick, "RGB");
	image_info->depth = 8;
	fun_CloneString(&(image_info->size), "6780x9685");
	(void) strcpy(image_info->filename, "tiger-A3-6780x9685.rgb");
	images=fun_ReadImage(image_info, exception);

	if (exception->severity != UndefinedException)
		fun_CatchException(exception);

	if (images == (Image*) NULL)
		exit(1);

	/*
	Convert the image to a thumbnail
	*/

	image = fun_RemoveFirstImageFromList(&images);
	if (image == (Image*) NULL)
		exit(1);

    /*
	clone_image = fun_CloneImage(image, 0, 0, MagickTrue, exception);
	if (clone_image == (Image*) NULL)
		exit(1);
    
    image = fun_DestroyImage(image);
    */

	crop_info.width = 3390;
	crop_info.height = 4842;   
    (void) strcpy(image_info->magick, "BMP");

    gettimeofday(&timeEnd, NULL);
    runTime = (timeEnd.tv_sec - timeStart.tv_sec) + (double)(timeEnd.tv_usec - timeStart.tv_usec) / 1000000;
    printf("Initialize time is is %lf\n", runTime);

	for (int index = 1; index <=4; index++)
	{
		gettimeofday(&timeStart, NULL);

        switch (index)
		{
		case 1:
			crop_info.x = 0;
			crop_info.y = 0;               
			break;
		case 2:
			crop_info.x = 3390;
			crop_info.y = 0;                
			break;
		case 3:
			crop_info.x = 0;
			crop_info.y = 4842;                
			break;
		case 4:
			crop_info.x = 3390;
			crop_info.y = 4842;               
			break;
		default:
			break;
		}

		crop_image = fun_CropImage(image, &crop_info, exception);
        
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
            resize_image = fun_ResizeImage(crop_image, 6780, 9685, LanczosFilter/*TriangleFilter*/, 1.0, exception);
            if (resize_image != (Image*) NULL)
            {
                (void) sprintf(resize_image->filename, "poster_2x2_A3_%d.bmp", index);
                fun_WriteImage(image_info, resize_image);
			    fun_DestroyImage(resize_image); 
            }
            			     
			fun_DestroyImage(crop_image);			
		}

        gettimeofday(&timeEnd, NULL);
        runTime = (timeEnd.tv_sec - timeStart.tv_sec) + (double)(timeEnd.tv_usec - timeStart.tv_usec) / 1000000;
        printf("%d resize is %lf\n", index, runTime);
	}

	/*
	Destory the image thumbnail and exit
	*/
	image_info = fun_DestroyImageInfo(image_info);
	image = fun_DestroyImage(image);
	exception = fun_DestroyExceptionInfo(exception);
	fun_MagickCoreTerminus();

	if (NULL != hLib)
	{
		dlclose(hLib);
		hLib = NULL;
	}

    runTime = (timeEnd.tv_sec - timeBegin.tv_sec) + (double)(timeEnd.tv_usec - timeBegin.tv_usec) / 1000000;
    printf("runTime is %lf\n", runTime);

	return(0);    
}