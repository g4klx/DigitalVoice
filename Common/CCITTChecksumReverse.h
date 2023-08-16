/*
 *	Copyright (C) 2009,2011 by Jonathan Naylor, G4KLX
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; version 2 of the License.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 */

#ifndef	CCITTChecksumReverse_H
#define	CCITTChecksumReverse_H

#include <wx/wx.h>

class CCCITTChecksumReverse {
public:
	CCCITTChecksumReverse();
	~CCCITTChecksumReverse();

	void update(const unsigned char* data, unsigned int length);
	void update(const bool* data);

	void result(unsigned char* data);
	void result(bool* data);

	bool check(const unsigned char* data);
	bool check(const bool* data);

	void reset();

private:
	union {
		wxUint16 m_crc16;
		wxUint8  m_crc8[2U];
	};
};

#endif
