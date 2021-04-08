 // This file is part of OpenCV project.
 // It is subject to the license terms in the LICENSE file found in the top-level directory
 // of this distribution and at http://opencv.org/license.html.
 
#include <opencv2/opencv.hpp>
#include <iostream> 
#include <chrono>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
 
using namespace std;
using namespace cv;

int main()
{

   FILE *fp = NULL;
   char *imagedata = NULL;
   int framesize = 0;

   struct timeval timeBegin, timeStart, timeEnd;
   double runTime = 0;

   gettimeofday(&timeBegin, NULL);

   fp = fopen("tiger-A4-4725x6780.rgb", "rb");
   framesize = 4725 * 6780 * 3;
   imagedata =  (char*) malloc (sizeof(char) * framesize);
   fread(imagedata, sizeof(char), framesize, fp);

   cv::Mat *pMatTemp = new cv::Mat(6780, 4725, CV_8UC3, imagedata);
   cv::Mat image;
   cv::Mat *pMat = NULL;

   cv::cvtColor(*pMatTemp, image, cv::COLOR_RGB2BGR); 
   
   pMat = &image;
   
   //case1: 2x2
   /*
   cv::Mat case1;
   auto timeStart1 = std::chrono::high_resolution_clock::now();
   cv::resize(*pMat, case1, cv::Size(), 2, 2, cv::INTER_LANCZOS4);
   auto timeEnd1 = std::chrono::high_resolution_clock::now();
   auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>( timeEnd1 - timeStart1 ).count();
   std::cout << "case1: 2x2, duration=" << duration1 << "\n";
   cv::imwrite("poster_2x2.bmp", case1 );

   //case2: 3x3
   /*
   cv::Mat case2;
   auto timeStart2 = std::chrono::high_resolution_clock::now();
   cv::resize(*pMat, case2, cv::Size(), 3, 3, cv::INTER_LANCZOS4);
   auto timeEnd2 = std::chrono::high_resolution_clock::now();
   auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>( timeEnd2 - timeStart2 ).count();
   std::cout << "case2: 3x3, duration=" << duration2 << "\n";
   cv::imwrite("poster_3x3.bmp", case2 );

   //case3: 4x4
   cv::Mat case3;
   auto timeStart3 = std::chrono::high_resolution_clock::now();
   cv::resize(*pMat, case3, cv::Size(), 4, 4, cv::INTER_LANCZOS4);
   auto timeEnd3 = std::chrono::high_resolution_clock::now();
   auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>( timeEnd3 - timeStart3 ).count();
   std::cout << "case3: 4x4, duration=" << duration3 << "\n";
   cv::imwrite("poster_4x4.bmp", case3 );
   */

   //case4: crop p2 and poster to 4x4
  
   for (int index = 1; index <=9; index++)
   {
      gettimeofday(&timeStart, NULL);

      switch (index)
      {
         case 1:
         {
            cv::Mat case1;
            cv::Rect rect1 = cv::Rect(0, 0, 1574, 2260);
            cv::Mat clipped1(*pMat, rect1);
            cv::resize(clipped1, case1, cv::Size(), 3, 3, cv::INTER_LANCZOS4);
            cv::imwrite("poster_3x3_A4_1.bmp", case1 );
            break;
         }
         case 2:
         {
            cv::Mat case2;
            cv::Rect rect2 = cv::Rect(1574, 0, 1574, 2260);
            cv::Mat clipped2(*pMat, rect2);
            cv::resize(clipped2, case2, cv::Size(), 3, 3, cv::INTER_LANCZOS4);
            cv::imwrite("poster_3x3_A4_2.bmp", case2 );
            break;
         }
         case 3:
         {
            cv::Mat case3;
            cv::Rect rect3 = cv::Rect(3149, 0, 1574, 2260); 
            cv::Mat clipped3(*pMat, rect3);
            cv::resize(clipped3, case3, cv::Size(), 3, 3, cv::INTER_LANCZOS4);
            cv::imwrite("poster_3x3_A4_3.bmp", case3 );
            break;
         }
         case 4:
         {
            cv::Mat case4;
            cv::Rect rect4 = cv::Rect(0, 2260, 1574, 2260);
            cv::Mat clipped4(*pMat, rect4);
            cv::resize(clipped4, case4, cv::Size(), 3, 3, cv::INTER_LANCZOS4);
            cv::imwrite("poster_3x3_A4_4.bmp", case4 );
            break;
         }
         case 5:
         {
            cv::Mat case5;
            cv::Rect rect5 = cv::Rect(1574, 2260, 1574, 2260);
            cv::Mat clipped5(*pMat, rect5);
            cv::resize(clipped5, case5, cv::Size(), 3, 3, cv::INTER_LANCZOS4);
            cv::imwrite("poster_3x3_A4_5.bmp", case5 );
            break;
         }
         case 6:
         {
            cv::Mat case6;
            cv::Rect rect6 = cv::Rect(3149, 2260, 1574, 2260);
            cv::Mat clipped6(*pMat, rect6);
            cv::resize(clipped6, case6, cv::Size(), 3, 3, cv::INTER_LANCZOS4);
            cv::imwrite("poster_3x3_A4_6.bmp", case6 );
            break;
         }
         case 7:
         {
            cv::Mat case7;
            cv::Rect rect7 = cv::Rect(0, 4520, 1574, 2260); 
            cv::Mat clipped7(*pMat, rect7);
            cv::resize(clipped7, case7, cv::Size(), 3, 3, cv::INTER_LANCZOS4);
            cv::imwrite("poster_3x3_A4_7.bmp", case7 );
            break;
         }
         case 8:
         {
            cv::Mat case8;
            cv::Rect rect8 = cv::Rect(1574, 4520, 1574, 2260);
            cv::Mat clipped8(*pMat, rect8);
            cv::resize(clipped8, case8, cv::Size(), 3, 3, cv::INTER_LANCZOS4);
            cv::imwrite("poster_3x3_A4_8.bmp", case8);
            break;
         }
         case 9:
         {
            cv::Mat case9;
            cv::Rect rect9 = cv::Rect(3149, 4520, 1574, 2260);
            cv::Mat clipped9(*pMat, rect9);
            cv::resize(clipped9, case9, cv::Size(), 3, 3, cv::INTER_LANCZOS4);
            cv::imwrite("poster_3x3_A4_9.bmp", case9 );
            break;
         }         
         default:
            break;
      }

      gettimeofday(&timeEnd, NULL);
      runTime = (timeEnd.tv_sec - timeStart.tv_sec) + (double)(timeEnd.tv_usec - timeStart.tv_usec) / 1000000;
      printf("%d runTime is %lf\n", index, runTime);
   }

   gettimeofday(&timeEnd, NULL);
   runTime = (timeEnd.tv_sec - timeBegin.tv_sec) + (double)(timeEnd.tv_usec - timeBegin.tv_usec) / 1000000;
   printf("runTime is %lf\n", runTime);
   
   free(imagedata);
   fclose(fp);

   return 0;
}
