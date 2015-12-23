// This file is part of CNCSVision, a computer vision related library
// This software is developed under the grant of Italian Institute of Technology
//
// Copyright (C) 2010-2014 Carlo Nicolini <carlo.nicolini@iit.it>
//
//
// CNCSVision is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// Alternatively, you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// CNCSVision is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License or the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License and a copy of the GNU General Public License along with
// CNCSVision. If not, see <http://www.gnu.org/licenses/>.

#include <iostream>
#include <vector>
#include "alp.h"
#include "ALPProjector.h"
#include "Timer.h"

#define N_TOTAL_SEQUENCES 10
using namespace std;

unsigned char* readBMP(char* filename, int *width, int *height, int *size)
{
    int i;
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    *width = *(int*)&info[18];
    *height = *(int*)&info[22];

    *size = 3 * (*width) * (*height);
    unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
    fclose(f);

    for(i = 0; i < size; i += 3)
    {
            unsigned char tmp = data[i];
            data[i] = data[i+2];
            data[i+2] = tmp;
    }

    return data;
}

void fillSquare(vector<unsigned char> &buf, int width, int height, int centerX, int centerY, int nPixelsX, int nPixelsY)
{  for (int i=0; i<width; i++)
   {  for (int j=0; j<height; j++)
      {  if ( i >= centerX-nPixelsX && i <= centerX+nPixelsX && j >= centerY-nPixelsY && j <= centerY+nPixelsY &&
               centerX+nPixelsX <= width && centerY+nPixelsY<=height &&
               centerX-nPixelsX >= 0 && centerY-nPixelsY>=0 )
            buf.at(i+j*width)=255;
         else
            buf.at(i+j*width)=0;
      }
   }
}

void fillPixel(vector<unsigned char> &buf,  int width, int height, int x, int y)
{  buf.at(x+y*width)=255;
}

int main( int argc, char *argv[] )
{  
   unsigned long int nPictures=1;
   //unsigned long int width = 1024;
   //unsigned long int height = 768;
   unsigned long int length = width*height*nPictures;

   int width,height,size;
   unsigned char *bmp = readBMP("helicoid.bmp",width,height,size);

   std::vector<unsigned char> data;
   data.resize(size);
   &data.at(0) = bmp;

   //fillSquare(data, width, height, width/2, height/2, 10,10);
   //fillPixel(data,  width, height, width/2, height/2);
   //for (int i=0; i<length; i++)
   //data[i] =	data[i]==255 ? 0 : 255;
   ALPProjector alp;
   try
   {  alp.init();
      alp.initLED();
      alp.setLED(15000,100);
      alp.inquire();
      alp.setPicturesTimeus(80); //timing in hertz
      alp.loadSequence(1,data.data());
      alp.start();
      cin.ignore(1E6,'\n');
      alp.stop();
   }
   catch (const std::exception &e)
   {  cerr << e.what() << endl << "Press Enter to exit..." ;
      cin.ignore(1E6,'\n');
      alp.cleanup();
   }
   return 0;
}
