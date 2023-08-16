/*
 *   Copyright (C) 2012 by Jonathan Naylor G4KLX
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

#include "DCSClientPreferences.h"

#include "DCSClientDefs.h"

const unsigned int BORDER_SIZE = 5U;

CDCSClientPreferences::CDCSClientPreferences(wxWindow* parent, int id, const wxString& callsign,
								   const wxString& readDevice, const wxString& writeDevice,
								   const wxString& dvdDevice, const wxString& message, bool bleep,
								   const wxString& ifaceType, unsigned int audioDelay, bool pttInvert,
								   bool squelchInvert, const wxString& startupReflector) :
wxDialog(parent, id, wxString(_("DCS Client Preferences")), wxDefaultPosition, wxDefaultSize, wxRESIZE_BORDER | wxDEFAULT_DIALOG_STYLE),
m_callsign(NULL),
m_soundcard(NULL),
m_dongle(NULL),
m_message(NULL),
m_bleep(NULL),
m_controller(NULL),
m_reflector(NULL)
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	wxNotebook* noteBook = new wxNotebook(this, -1);

	m_callsign = new CDCSClientCallsignSet(noteBook, -1, APPLICATION_NAME, callsign);
	noteBook->AddPage(m_callsign, _("Callsign"), true);

	m_soundcard = new CSoundcardSet(noteBook, -1, APPLICATION_NAME, readDevice, writeDevice);
	noteBook->AddPage(m_soundcard, _("Sound Card"), false);

	m_controller = new CDCSClientControllerSet(noteBook, -1, APPLICATION_NAME, ifaceType, audioDelay, pttInvert, squelchInvert);
	noteBook->AddPage(m_controller, _("Controller"), false);

	m_dongle = new CDVDongleSet(noteBook, -1, APPLICATION_NAME, dvdDevice);
	noteBook->AddPage(m_dongle, _("DV-Dongle"), false);

	m_message = new CMessageSet(noteBook, -1, APPLICATION_NAME, message);
	noteBook->AddPage(m_message, _("Message"), false);

	m_bleep = new CBleepSet(noteBook, -1, APPLICATION_NAME, bleep);
	noteBook->AddPage(m_bleep, _("Bleep"), false);

	m_reflector = new CDCSClientReflectorSet(noteBook, -1, APPLICATION_NAME, startupReflector);
	noteBook->AddPage(m_reflector, _("Startup"), false);

	mainSizer->Add(noteBook, 1, wxALL | wxGROW, BORDER_SIZE);

	mainSizer->Add(CreateButtonSizer(wxOK | wxCANCEL), 0, wxALL | wxALIGN_RIGHT, BORDER_SIZE);

	SetAutoLayout(true);
	Layout();

	mainSizer->Fit(this);
	mainSizer->SetSizeHints(this);

	SetSizer(mainSizer);
}

CDCSClientPreferences::~CDCSClientPreferences()
{
}

bool CDCSClientPreferences::Validate()
{
	if (!m_callsign->Validate())
		return false;

	if (!m_soundcard->Validate())
		return false;

	if (!m_dongle->Validate())
		return false;

	if (!m_message->Validate())
		return false;

	if (!m_bleep->Validate())
		return false;

	if (!m_controller->Validate())
		return false;

	return m_reflector->Validate();
}

wxString CDCSClientPreferences::getCallsign() const
{
	return m_callsign->getCallsign();
}

wxString CDCSClientPreferences::getReadDevice() const
{
	return m_soundcard->getReadDevice();
}

wxString CDCSClientPreferences::getWriteDevice() const
{
	return m_soundcard->getWriteDevice();
}

wxString CDCSClientPreferences::getDVDDevice() const
{
	return m_dongle->getDevice();
}

wxString CDCSClientPreferences::getMessage() const
{
	return m_message->getMessage();
}

bool CDCSClientPreferences::getBleep() const
{
	return m_bleep->getBleep();
}

wxString CDCSClientPreferences::getIfaceType() const
{
	return m_controller->getType();
}

unsigned int CDCSClientPreferences::getAudioDelay() const
{
	return m_controller->getDelay();
}

bool CDCSClientPreferences::getPTTInvert() const
{
	return m_controller->getPTTInvert();
}

bool CDCSClientPreferences::getSquelchInvert() const
{
	return m_controller->getSquelchInvert();
}

wxString CDCSClientPreferences::getStartupReflector() const
{
	return m_reflector->getReflector();
}
