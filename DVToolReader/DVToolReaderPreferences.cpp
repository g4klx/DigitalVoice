/*
 *   Copyright (C) 2009,2010 by Jonathan Naylor G4KLX
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

#include "DVToolReaderPreferences.h"
#include "DVToolReaderDefs.h"

#include <wx/notebook.h>

CDVToolReaderPreferences::CDVToolReaderPreferences(wxWindow* parent, int id, const wxString& device, const wxString& soundcard, bool bleep) :
wxDialog(parent, id, wxString(_("DVTool Reader Preferences")), wxDefaultPosition, wxDefaultSize, wxRESIZE_BORDER | wxDEFAULT_DIALOG_STYLE),
m_soundcard(NULL),
m_dongle(NULL),
m_bleep(NULL)
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	wxNotebook* noteBook = new wxNotebook(this, -1);

	m_soundcard = new CDVToolReaderUserSoundcardSet(noteBook, -1, APPLICATION_NAME, soundcard);
	noteBook->AddPage(m_soundcard, _("Sound Card"), true);

	m_dongle = new CDVDongleSet(noteBook, -1, APPLICATION_NAME, device);
	noteBook->AddPage(m_dongle, _("DV-Dongle"), false);

	m_bleep = new CBleepSet(noteBook, -1, APPLICATION_NAME, bleep);
	noteBook->AddPage(m_bleep, _("Bleep"), false);

	mainSizer->Add(noteBook, 1, wxALL | wxGROW, BORDER_SIZE);

	mainSizer->Add(CreateButtonSizer(wxOK | wxCANCEL), 0, wxALL | wxALIGN_RIGHT, BORDER_SIZE);

	SetAutoLayout(true);
	Layout();

	mainSizer->Fit(this);
	mainSizer->SetSizeHints(this);

	SetSizer(mainSizer);
}

CDVToolReaderPreferences::~CDVToolReaderPreferences()
{
}

bool CDVToolReaderPreferences::Validate()
{
	if (!m_soundcard->Validate())
		return false;

	if (!m_dongle->Validate())
		return false;

	return m_bleep->Validate();
}

wxString CDVToolReaderPreferences::getDevice() const
{
	return m_dongle->getDevice();
}

wxString CDVToolReaderPreferences::getSoundcard() const
{
	return m_soundcard->getDevice();
}

bool CDVToolReaderPreferences::getBleep() const
{
	return m_bleep->getBleep();
}
