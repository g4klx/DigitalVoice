/*
 *   Copyright (C) 2010,2011,2012 by Jonathan Naylor G4KLX
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

#ifndef	GMSKModemLibUsb_H
#define	GMSKModemLibUsb_H

#include "HeaderData.h"
#include "GMSKModem.h"
#include "Utils.h"

#include <wx/wx.h>
#if defined(WIN32)
#include <wx/dynlib.h>
#include "lusb0_usb.h"
#else
#include <libusb-1.0/libusb.h>
#endif

class CGMSKModemLibUsb : public IGMSKModem {
public:
	CGMSKModemLibUsb(unsigned int address);
	virtual ~CGMSKModemLibUsb();

	virtual bool open();

	virtual bool isBroken() const;

	virtual CHeaderData* readHeader();
	virtual int readData(unsigned char* data, unsigned int length, bool& end);

	virtual TRISTATE getPTT();
	virtual bool setPTT(bool on);

	virtual TRISTATE hasSpace();

	virtual bool writeHeader(const CHeaderData& header);
	virtual int writeData(const unsigned char* data, unsigned int length);

	virtual void close();

private:
	unsigned int             m_address;
#if defined(WIN32)
	usb_dev_handle*          m_dev;

	static wxDynamicLibrary* m_library;
	static bool              m_loaded;

	static void            (*m_usbInit)();
	static int             (*m_usbFindBusses)();
	static int             (*m_usbFindDevices)();
	static usb_bus*        (*m_usbGetBusses)();
	static usb_dev_handle* (*m_usbOpen)(struct usb_device*);
	static int             (*m_usbSetConfiguration)(usb_dev_handle*, int);
	static int             (*m_usbControlMsg)(usb_dev_handle*, int, int, int, int, char*, int, int);
	static char*           (*m_usbStrerror)();
	static int             (*m_usbClose)(usb_dev_handle*);
#else
	libusb_context*          m_context;
	libusb_device_handle*    m_handle;
#endif
	bool                     m_broken;
};

#endif
