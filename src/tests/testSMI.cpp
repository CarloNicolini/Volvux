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


#include "StdAfx.h"
#include <iostream>
#include "SmartMotor.h"
#include <windows.h>
#import "IntegMotorInterface.tlb"
#include "SMIDefs.h"
#define IDM_ABOUTBOX                    0x0010
#define IDD_ABOUTBOX                    100
#define IDS_ABOUTBOX                    101
#define IDD_USEENGINE_DIALOG            102
#define IDR_MAINFRAME                   128
#define IDC_NOOFMOTORS                  1000
#define IDC_ADDRESSCHAIN                1001
#define IDC_INITENGINE                  1002
#define IDC_DETECT232                   1002
#define IDC_COMMAND                     1003
#define IDC_RESPONSE                    1004
#define IDC_SEND                        1005
#define IDC_GET                         1006
#define IDC_COMCOMBO                    1007
#define IDC_OPEN                        1008
#define IDC_BAUDRATECOMBO               1009
#define IDC_CURRENTMOTOR                1010
#define IDC_SENDANDGET                  1011
#define IDC_HOSTMODE                    1012
#define IDC_PATHGEN                     1013
#define IDC_INITRS485                   1013
#define IDC_LINE                        1014
#define IDC_CIRCLE                      1015
#define IDC_BUTTON1                     1016
#define IDC_DETECTRS485                 1016
#define IDC_FILENAME                    1017
#define IDC_SCAN                        1018
#define IDC_MAKESMX                     1019
#define IDC_DOWNLOAD                    1020
#define IDC_NEXTERROR                   1021
#define IDC_ERRORTEXT                   1022
#define IDC_NOOFERRORS                  1023
#define IDC_NOOFWARNINGS                1024
#define IDC_ERRORPOS                    1025
#define IDC_ERRORTYPE                   1026
#define IDC_FIRSTERROR                  1027
#define IDC_PERCENT                     1028
#define IDC_ADDRESSSERVOS               1029
#define IDC_MAXADDRESS                  1030
#define IDC_MOTORCHANNEL                1031
#define IDC_GETSN                       1032
#define IDC_GETMODELSTR                 1033
#define IDC_PROGRESS                    1034
#define IDC_STATUS                      1035
#define IDC_VERSION                     1036
#define IDC_UPLOAD                      1037
#define IDC_CLEARPROGRAM                1038
#define IDC_CLOSE                       1039
#define IDC_CHECK1                      1040
#define IDC_CUSTOM1                     1041
#define INCREMENTS_PER_REVOLUTION		8000

using namespace INTEGMOTORINTERFACELib;

#include <iostream>
#include <fstream>
using namespace std;

int main()
{ 
   std::ofstream outfile; outfile.open("C:\\workspace\\Volvux\\build\\Debug\\data.txt",'w');
   
   SmartMotor smart;
   long abspos; 
   smart.init();
   try
   {  
	   smart.startRotation(0);
	   smart.openPort();
	   smart.detect232();
	   smart.addressChain();
	   if (smart.getAbsolutePosition() != 0) 
	   {
		   smart.goToDefaultPosition(1000000);
	   }
	   abspos = 0;
	   smart.startRotation(100000);
	   while (true)
	   {
		   abspos = smart.getAbsolutePosition();
		   int r = abspos%INCREMENTS_PER_REVOLUTION;
		   outfile << r << endl;
		   if (r< 8000 && r>7990)
			   Beep(440, 200);
	   }
	   smart.startRotation(0);
   }
   catch (_com_error e)
   {
	   throw std::runtime_error(BSTR2STR(e.Description()));
   }
}