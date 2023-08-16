/*
 *   Copyright (C) 2009 by Jonathan Naylor G4KLX
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

#ifndef	DVToolReaderFrame_H
#define	DVToolReaderFrame_H

#include "DVToolReaderDefs.h"
#include "MessageData.h"
#include "HeaderData.h"

#include <wx/wx.h>

class CDVToolReaderFrame : public wxFrame {
public:
	CDVToolReaderFrame(const wxString& title = wxEmptyString);
	virtual ~CDVToolReaderFrame();

	virtual void onOpen(wxCommandEvent& event);
	virtual void onQuit(wxCommandEvent& event);

	virtual void onPreferences(wxCommandEvent& event);

	virtual void onAbout(wxCommandEvent& event);

	virtual void onClose(wxCloseEvent& event);

	virtual void onMessage(wxEvent& event);
	virtual void onHeader(wxEvent& event);
	virtual void onError(wxEvent& event);

	virtual void showMessage(CMessageData* message);
	virtual void showHeader(CHeaderData* header);
	virtual void error(const wxString& error);

private:
	wxStaticText* m_fileName;
	wxStaticText* m_your;
	wxStaticText* m_my;
	wxStaticText* m_rpt1;
	wxStaticText* m_rpt2;
	wxStaticText* m_flags;
	wxStaticText* m_message;

	DECLARE_EVENT_TABLE()

	wxMenuBar* createMenuBar();
};

#endif
