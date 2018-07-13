/*****************************************************************************
 *  Copyright (c) 2012, lcad.inf.ufes.br; 2009, OpenJAUS.com
 *  All rights reserved.
 *  
 *  This file is part of OpenJAUS.  OpenJAUS is distributed under the BSD 
 *  license.  See the LICENSE file for details.
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of the University of Florida nor the names of its 
 *       contributors may be used to endorse or promote products derived from 
 *       this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ****************************************************************************/
// File Name: reportSignalsMessage.h
//
// Written By: Alberto F. De Souza
//
// Version: 0.0.1
//
// Date: 02/21/2012
//
// Description: This file defines the attributes of a ReportSignalsMessage

#ifndef REPORT_SIGNALS_MESSAGE_H
#define REPORT_SIGNALS_MESSAGE_H

#include <xgv_client/xgv_client.h>
#include <jaus/jaus.h>

#ifndef JAUS_SIGNALS_PV
#define JAUS_SIGNALS_PV
#define JAUS_SIGNALS_PV_TURN_SIGNAL_BIT     0
#define JAUS_SIGNALS_PV_HORN_BIT        1
#define JAUS_SIGNALS_PV_HEADLIGHTS_BIT      2
#endif

typedef struct
{
    // Include all parameters from a JausMessage structure:
    // Header Properties
    struct
    {
        // Properties by bit fields
        #ifdef JAUS_BIG_ENDIAN
            JausUnsignedShort reserved:2;
            JausUnsignedShort version:6;
            JausUnsignedShort expFlag:1;
            JausUnsignedShort scFlag:1;
            JausUnsignedShort ackNak:2;
            JausUnsignedShort priority:4; 
        #elif JAUS_LITTLE_ENDIAN
            JausUnsignedShort priority:4; 
            JausUnsignedShort ackNak:2;
            JausUnsignedShort scFlag:1; 
            JausUnsignedShort expFlag:1;
            JausUnsignedShort version:6; 
            JausUnsignedShort reserved:2;
        #else
            #error "Please define system endianess (see jaus.h)"
        #endif
    }properties;

    JausUnsignedShort commandCode; 

    JausAddress destination;

    JausAddress source;

    JausUnsignedInteger dataSize;

    JausUnsignedInteger dataFlag;
    
    JausUnsignedShort sequenceNumber;

    JausByte version;               // Byte (VictorTango message version. Currently must have value = 0)
    JausByte presenceVector;
    JausByte turnSignal;                // 0: Off, 1: Left, 2: Right, 3: Flashes, 4-255: Reserved
    JausByte hornStatus;                // 0: Off, 1: On
    JausByte hornPeriodOn;              // Unused
    JausByte hornPeriodOff;             // Unused
    JausByte headlightsStatus;          // Bits 0-2: 0: Off, 1: Parking Lights, 2: On; 
                            // Bit 3: High beans (T: On, F: Off), only if Lights Status = 2; 
                            // Bit 4: Fog lights (T: On, F: Off), only if Lights Status = 2; 
                            // Bits 5-7: Reserved
    JausByte lightsPeriodOn;            // Unused
    JausByte lightsPeriodOff;           // Unused
    
}ReportSignalsMessageStruct;

typedef ReportSignalsMessageStruct* ReportSignalsMessage;

JAUS_EXPORT ReportSignalsMessage reportSignalsMessageCreate(void);
JAUS_EXPORT void reportSignalsMessageDestroy(ReportSignalsMessage);

JAUS_EXPORT JausBoolean reportSignalsMessageFromBuffer(ReportSignalsMessage message, unsigned char* buffer, unsigned int bufferSizeBytes);
JAUS_EXPORT JausBoolean reportSignalsMessageToBuffer(ReportSignalsMessage message, unsigned char *buffer, unsigned int bufferSizeBytes);

JAUS_EXPORT ReportSignalsMessage reportSignalsMessageFromJausMessage(JausMessage jausMessage);
JAUS_EXPORT JausMessage reportSignalsMessageToJausMessage(ReportSignalsMessage message);

JAUS_EXPORT unsigned int reportSignalsMessageSize(ReportSignalsMessage message);

JAUS_EXPORT char* reportSignalsMessageToString(ReportSignalsMessage message);
#endif // REPORT_SIGNALS_MESSAGE_H
