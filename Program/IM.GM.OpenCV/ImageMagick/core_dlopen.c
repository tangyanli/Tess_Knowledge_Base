//---------------
/* How to build */
/* gcc -o core_dlopen core_dlopen.c `pkg-config --cflags MagickCore` -ldl */
//----------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dlfcn.h>
#include <magick/MagickCore.h>

int main(int argc, char **argv)
{
    ExceptionInfo *exception;
    Image *image, *images, *crop_image, *resize_image, *thumbnails;
    ImageInfo *image_info;

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
    void (*fun_MagickCoreTerminus)(void);

    if (argc != 3)
    {
     (void) fprintf(stdout,"Usage: %s image thumbnail\n",argv[0]);
      exit(0);
    }

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
    (void) strcpy(image_info->filename, argv[1]);
    images=fun_ReadImage(image_info, exception);

    if (exception->severity != UndefinedException)
        fun_CatchException(exception);

    if (images == (Image*) NULL)
        exit(1);

    /*
        Convert the image to a thumbnail
    */
    thumbnails = fun_NewImageList();
    while ((image = fun_RemoveFirstImageFromList(&images)) != (Image*) NULL)
    {
        resize_image = fun_ResizeImage(image, 678, 968, LanczosFilter, 1, exception);
        //resize_image = ScaleImage(image, 106, 80, exception);
        if (resize_image == (Image*) NULL)
            fun_MagickError(exception->severity,exception->reason,exception->description);
            (void) fun_AppendImageToList(&thumbnails, resize_image);
            fun_DestroyImage(image);
    }

    /*
        Write the image thumbnail.
    */
   (void) strcpy(thumbnails->filename, argv[2]);
   fun_WriteImage(image_info, thumbnails);

   /*
        Destory the image thumbnail and exit
   */
  thumbnails = fun_DestroyImageList(thumbnails);
  image_info = fun_DestroyImageInfo(image_info);
  exception = fun_DestroyExceptionInfo(exception);
  fun_MagickCoreTerminus();

  if (NULL != hLib)
  {
      dlclose(hLib);
      hLib = NULL;
  }

  return(0);    
}