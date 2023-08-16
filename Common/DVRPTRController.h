/*
 *   Copyright (C) 2011,2012 by Jonathan Naylor G4KLX
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef	DVRPTRController_H
#define	DVRPTRController_H

#include "HeaderData.h"
#include "Utils.h"

#include <wx/wx.h>

enum DATA_QUEUE_TYPE {
	DQT_NONE,
	DQT_HEADER,
	DQT_DATA,
	DQT_EOT,
	DQT_LOST,
	DQT_START
};

class IDVRPTRController {
public:
	virtual bool open() = 0;

	virtual bool getPTT() const = 0;

	virtual bool hasSpace() = 0;

	virtual DATA_QUEUE_TYPE readQueue(unsigned char* data, unsigned int& length) = 0;

	virtual bool writeHeader(const CHeaderData& header) = 0;
	virtual bool writeData(const unsigned char* data, unsigned int length, bool end) = 0;

	virtual void close() = 0;

private:
};

#endif

