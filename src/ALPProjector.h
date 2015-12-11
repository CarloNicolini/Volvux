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


#ifndef _ALP_PROJECTOR_H_
#define _ALP_PROJECTOR_H_

//#define ALP_SUPPORT 1

#include <iostream>
#include <vector>
#include <string>

#ifdef ALP_SUPPORT
#include <windows.h>
#include "alp.h"
#endif

static const std::string MESSAGE_ALP_INIT("Initialize the ALP ...");
static const std::string ALP_ERROR_ALP_INIT("Initialization of the ALP failed.");
static const std::string ALP_ERROR_ALP_FREE("Clear-up of the ALP failed.");
static const std::string ALP_ERROR_SEQ_ALLOC("Allocation of ALP sequence memory failed.");
static const std::string ALP_ERROR_ALP_REINIT("Re-initialization of the ALP not allowed.");
static const std::string ALP_ERROR_ALP_NOT_INIT("ALP not initialized.");
static const std::string ALP_ERROR_DMD_TYPE("Unknown DMD Type.");
static const std::string ALP_ERROR_SEQ_NOT_INIT("No sequence allocated.");

/*
#define    IDS_SEQ_NUMBER          ("Number of sequences: %i")
#define    IDS_SEQ_ACTIVE          ("Active sequence: %i")
#define    IDS_SEQ_PICTIME         ("Picture time: %i µs")
#define    IDS_SEQ_MINPICTIME      ("Minimum picture time: %i µs")
#define    IDS_DEVICE_VERSION      ("ALP Version: %i.%i")
#define    IDS_DEVICE_NUMBER       "Serial Number: %i"
#define    IDS_DEVICE_MEMORY       "Memory: %i of %i binary frames free"
*/
#define SEQU_MAX 32

#ifndef ALP_DEFAULT
#define ALP_DEFAULT 0L
#endif

class ALPProjector
{
public:
    ALPProjector();
    ~ALPProjector();

    // Generic methods for ALP interface
    void init();
    void initLED();
    void inquire();
    void cleanup();

    // Setter methods
    void setLED(long int ledCurrentMilliAmperes, long int ledBrightnessPercent);
    void setPicturesTimeus(long int pictureTime);
    void setSequenceQueueMode();

    // Getter methods
    long int getMinimumPictureTime() const;

    // Sequence methods
    long int loadSequence(unsigned int picturesNumber, unsigned char *imageSequence=NULL);
    void changeSequence(long int sequenceID);
    void removeSequence(long int sequenceID);
    void cleanAllSequences();

    // Projector methods
    void start();
    void stop();
    void loopAllSequences();
    
    // Member variables as in the AlpSample example
    bool        m_bAlpInit;                // ALP initialization status
    bool        m_bAlpLEDInit;            // ALP LED initialization status
    bool        m_bDisp;                // display active
    
    unsigned long        m_AlpId;                // ALP device ID
    unsigned long      m_AlpLED_id;
    std::vector<unsigned long> m_AlpSeqId;

    long int    m_nDmdType;                // DMD type (ALP_DMDTYPE_...)
    long int    m_nSizeX, m_nSizeY;        // DMD size (pixels X*Y)
    long int    m_AlpSeqDisp;            // ALP sequence selected for display
    long int    m_FrameMemory;            // number of binary frames
    long int    m_BitNum;                // number of bits
    long int    m_PicNum;                // number of pictures
    
    long int sequenceID;

    // Data to display
    unsigned char*        m_pData;            // sequence data

    // Timing parameters, selected to default settings
    static const long m_Timing_IlluminateTime=ALP_DEFAULT;
    static const long m_Timing_SynchDelay = ALP_DEFAULT;  //delay of the display start with respect to the trigger output (master mode)
    static const long m_Timing_SynchPulseWidth = ALP_DEFAULT; //length of the trigger signal, the maximum value is ALP_PICTURE_TIME
    static const long m_Timing_TriggerInDelay = ALP_DEFAULT; //delay of the start of the display with respect to the trigger input signal (slave mode)
    long int m_Timing_PictureTime;

    // Helper and secondary methods
    void initWheel(unsigned char *buf, int num);
};


#ifndef ALP_SUPPORT
#define ALP_OK				0x00000000L		/*	successfull execution */
#define ALP_NOT_ONLINE			1001L		/*	The specified ALP has not been found or is not ready. */
#define ALP_NOT_IDLE			1002L		/*	The ALP is not in idle state. */
#define ALP_NOT_AVAILABLE		1003L		/*	The specified ALP identifier is not valid. */
#define ALP_NOT_READY			1004L		/*	The specified ALP is already allocated. */
#define ALP_PARM_INVALID		1005L		/*	One of the parameters is invalid. */
#define ALP_ADDR_INVALID		1006L		/*	Error accessing user data. */
#define ALP_MEMORY_FULL			1007L		/*	The requested memory is not available. */
#define ALP_SEQ_IN_USE			1008L		/*	The sequence specified is currently in use. */
#define ALP_HALTED				1009L		/*	The ALP has been stopped while image data transfer was active. */
#define ALP_ERROR_INIT			1010L		/*	Initialization error. */
#define ALP_ERROR_COMM			1011L		/*	Communication error. */
#define ALP_DEVICE_REMOVED		1012L		/*	The specified ALP has been removed. */
#endif

#define ALP_TRY(ALPcall){ \
int _alpResult = ALPcall; \
switch (_alpResult)\
{\
    case ALP_OK:\
    break;\
    case ALP_PARM_INVALID:\
        throw std::runtime_error("Invalid ALP parameter");\
    break;\
    case ALP_ADDR_INVALID:\
        throw std::runtime_error("Invalid ALP address");\
    break;\
    case ALP_NOT_READY:\
        throw std::runtime_error("ALP not ready");\
    break;\
    case ALP_NOT_IDLE:\
        throw std::runtime_error("ALP not idle");\
    break;\
    case ALP_SEQ_IN_USE:\
        throw std::runtime_error("ALP sequence is in use");\
    break;\
    case ALP_NOT_AVAILABLE:\
        throw std::runtime_error("ALP is not available");\
    break;\
    case ALP_ERROR_COMM:\
        throw std::runtime_error("ALP communication error");\
    break;\
    case ALP_DEVICE_REMOVED:\
        throw std::runtime_error("ALP device is removed");\
    break;\
}\
}


#endif
