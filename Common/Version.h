/*
 *	Copyright (C) 2010-2013 by Jonathan Naylor, G4KLX
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

#ifndef	Version_H
#define	Version_H

#include <wx/wx.h>

const wxString VENDOR_NAME = wxT("G4KLX");

const wxString SVNREV = wxT("$Revision: 270 $ on $Date: 2013-02-03 19:03:42 +0000 (Sun, 03 Feb 2013) $");

#if defined(__WXDEBUG__)
const wxString VERSION = wxT("20130203 - DEBUG");
#else
const wxString VERSION = wxT("20130203");
#endif

#endif
