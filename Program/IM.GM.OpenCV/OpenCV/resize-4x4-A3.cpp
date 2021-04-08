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

   fp = fopen("tiger-A3-6780x9685.rgb", "rb");
   framesize = 6780 * 9685 * 3;
   imagedata =  (char*) malloc (sizeof(char) * framesize);
   fread(imagedata, sizeof(char), framesize, fp);

   cv::Mat *pMatTemp = new cv::Mat(9685, 6780, CV_8UC3, imagedata);
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

   for (int index = 1; index <=16; index++)
   {
      gettimeofday(&timeStart, NULL);

      switch (index)
      {
         case 1:
         {
            cv::Mat case1;
            cv::Rect rect1 = cv::Rect(0, 0, 1695, 2421);
            cv::Mat clipped1(*pMat, rect1);
            cv::resize(clipped1, case1, cv::Size(), 4, 4, cv::INTER_LANCZOS4);
            cv::imwrite("poster_4x4_A3_1.bmp", case1 );
            break;
         }
         case 2:
         {
            cv::Mat case2;
            cv::Rect rect2 = cv::Rect(1695, 0, 1695, 2421);
            cv::Mat clipped2(*pMat, rect2);
            cv::resize(clipped2, case2, cv::Size(), 4, 4, cv::INTER_LANCZOS4);
            cv::imwrite("poster_4x4_A3_2.bmp", case2 );
            break;
         }
         case 3:
         {
            cv::Mat case3;
            cv::Rect rect3 = cv::Rect(3390, 0, 1695, 2421); 
            cv::Mat clipped3(*pMat, rect3);
            cv::resize(clipped3, case3, cv::Size(), 4, 4, cv::INTER_LANCZOS4);
            cv::imwrite("poster_4x4_A3_3.bmp", case3 );
            break;
         }
         case 4:
         {
            cv::Mat case4;
            cv::Rect rect4 = cv::Rect(5085, 0, 1695, 2421);
            cv::Mat clipped4(*pMat, rect4);
            cv::resize(clipped4, case4, cv::Size(), 4, 4, cv::INTER_LANCZOS4);
            cv::imwrite("poster_4x4_A3_4.bmp", case4 );
            break;
         }
         case 5:
         {
            cv::Mat case5;
            cv::Rect rect5 = cv::Rect(0, 2421, 1695, 2421);
            cv::Mat clipped5(*pMat, rect5);
            cv::resize(clipped5, case5, cv::Size(), 4, 4, cv::INTER_LANCZOS4);
            cv::imwrite("poster_4x4_A3_5.bmp", case5 );
            break;
         }
         case 6:
         {
            cv::Mat case6;
            cv::Rect rect6 = cv::Rect(1695, 2421, 1695, 2421);
            cv::Mat clipped6(*pMat, rect6);
            cv::resize(clipped6, case6, cv::Size(), 4, 4, cv::INTER_LANCZOS4);
            cv::imwrite("poster_4x4_A3_6.bmp", case6 );
            break;
         }
         case 7:
         {
            cv::Mat case7;
            cv::Rect rect7 = cv::Rect(3390, 2421, 1695, 2421); 
            cv::Mat clipped7(*pMat, rect7);
            cv::resize(clipped7, case7, cv::Size(), 4, 4, cv::INTER_LANCZOS4);
            cv::imwrite("poster_4x4_A3_7.bmp", case7 );
            break;
         }
         case 8:
         {
            cv::Mat case8;
            cv::Rect rect8 = cv::Rect(5085, 2421, 1695, 2421);
            cv::Mat clipped8(*pMat, rect8);
            cv::resize(clipped8, case8, cv::Size(), 4, 4, cv::INTER_LANCZOS4);
            cv::imwrite("poster_4x4_A3_8.bmp", case8);
            break;
         }
         case 9:
         {
            cv::Mat case9;
            cv::Rect rect9 = cv::Rect(0, 4842, 1695, 2421);
            cv::Mat clipped9(*pMat, rect9);
            cv::resize(clipped9, case9, cv::Size(), 4, 4, cv::INTER_LANCZOS4);
            cv::imwrite("poster_4x4_A3_9.bmp", case9 );
            break;
         }
         case 10:
         {
            cv::Mat case10;
            cv::Rect rect10 = cv::Rect(1695, 4842, 1695, 2421);
            cv::Mat clipped10(*pMat, rect10);
            cv::resize(clipped10, case10, cv::Size(), 4, 4, cv::INTER_LANCZOS4);
            cv::imwrite("poster_4x4_A3_10.bmp", case10 );
            break;
         }
         case 11:
         {
            cv::Mat case11;
            cv::Rect rect11 = cv::Rect(3390, 4842, 1695, 2421); 
            cv::Mat clipped11(*pMat, rect11);
            cv::resize(clipped11, case11, cv::Size(), 4, 4, cv::INTER_LANCZOS4);
            cv::imwrite("poster_4x4_A3_11.bmp", case11 );
            break;
         }
         case 12:
         {
            cv::Mat case12;
            cv::Rect rect12 = cv::Rect(5085, 4842, 1695, 2421);
            cv::Mat clipped12(*pMat, rect12);
            cv::resize(clipped12, case12, cv::Size(), 4, 4, cv::INTER_LANCZOS4);
            cv::imwrite("poster_4x4_A3_12.bmp", case12 );
            break;
         }
         case 13:
         {
            cv::Mat case13;
            cv::Rect rect13 = cv::Rect(0, 7264, 1695, 2421);
            cv::Mat clipped13(*pMat, rect13);
            cv::resize(clipped13, case13, cv::Size(), 4, 4, cv::INTER_LANCZOS4);
            cv::imwrite("poster_4x4_A3_13.bmp", case13 );
            break;
         }
         case 14:
         {
            cv::Mat case14;
            cv::Rect rect14 = cv::Rect(1695, 7264, 1695, 2421);
            cv::Mat clipped14(*pMat, rect14);
            cv::resize(clipped14, case14, cv::Size(), 4, 4, cv::INTER_LANCZOS4);
            cv::imwrite("poster_4x4_A3_14.bmp", case14 );
            break;
         }
         case 15:
         {
            cv::Mat case15;
            cv::Rect rect15 = cv::Rect(3390, 7264, 1695, 2421); 
            cv::Mat clipped15(*pMat, rect15);
            cv::resize(clipped15, case15, cv::Size(), 4, 4, cv::INTER_LANCZOS4);
            cv::imwrite("poster_4x4_A3_15.bmp", case15 );
            break;
         }
         case 16:
         {
            cv::Mat case16;
            cv::Rect rect16 = cv::Rect(5085, 7264, 1695, 2421);
            cv::Mat clipped16(*pMat, rect16);
            cv::resize(clipped16, case16, cv::Size(), 4, 4, cv::INTER_LANCZOS4);
            cv::imwrite("poster_4x4_A3_16.bmp", case16 );
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
