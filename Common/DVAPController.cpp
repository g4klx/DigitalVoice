/*
 *   Copyright (C) 2011,2012,2013 by Jonathan Naylor G4KLX
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

#include "CCITTChecksumReverse.h"
#include "DVAPController.h"
#include "DStarDefines.h"

const unsigned char DVAP_REQ_NAME[] = {0x04, 0x20, 0x01, 0x00};
const unsigned int  DVAP_REQ_NAME_LEN = 4U;

const unsigned char DVAP_RESP_NAME[] = {0x10, 0x00, 0x01, 0x00, 'D', 'V', 'A', 'P', ' ', 'D', 'o', 'n', 'g', 'l', 'e', 0x00};
const unsigned int  DVAP_RESP_NAME_LEN = 16U;

const unsigned char DVAP_REQ_SERIAL[] = {0x04, 0x20, 0x02, 0x00};
const unsigned int  DVAP_REQ_SERIAL_LEN = 4U;

const unsigned char DVAP_RESP_SERIAL[] = {0x0C, 0x00, 0x02, 0x00};
const unsigned int  DVAP_RESP_SERIAL_LEN = 4U;

const unsigned char DVAP_REQ_FIRMWARE[] = {0x05, 0x20, 0x04, 0x00, 0x01};
const unsigned int  DVAP_REQ_FIRMWARE_LEN = 5U;

const unsigned char DVAP_RESP_FIRMWARE[] = {0x07, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00};
const unsigned int  DVAP_RESP_FIRMWARE_LEN = 7U;

const unsigned char DVAP_REQ_MODULATION[] = {0x05, 0x00, 0x28, 0x00, 0x01};
const unsigned int  DVAP_REQ_MODULATION_LEN = 5U;

const unsigned char DVAP_RESP_MODULATION[] = {0x05, 0x00, 0x28, 0x00, 0x01};
const unsigned int  DVAP_RESP_MODULATION_LEN = 5U;

const unsigned char DVAP_REQ_MODE[] = {0x05, 0x00, 0x2A, 0x00, 0x00};
const unsigned int  DVAP_REQ_MODE_LEN = 5U;

const unsigned char DVAP_RESP_MODE[] = {0x05, 0x00, 0x2A, 0x00, 0x00};
const unsigned int  DVAP_RESP_MODE_LEN = 5U;

const unsigned char DVAP_REQ_SQUELCH[] = {0x05, 0x00, 0x80, 0x00, 0x00};
const unsigned int  DVAP_REQ_SQUELCH_LEN = 5U;

const unsigned char DVAP_RESP_SQUELCH[] = {0x05, 0x00, 0x80, 0x00, 0x00};
const unsigned int  DVAP_RESP_SQUELCH_LEN = 5U;

const unsigned char DVAP_REQ_POWER[] = {0x06, 0x00, 0x38, 0x01, 0x00, 0x00};
const unsigned int  DVAP_REQ_POWER_LEN = 6U;

const unsigned char DVAP_RESP_POWER[] = {0x06, 0x00, 0x38, 0x01, 0x00, 0x00};
const unsigned int  DVAP_RESP_POWER_LEN = 6U;

const unsigned char DVAP_REQ_FREQUENCY[] = {0x08, 0x00, 0x20, 0x02, 0x00, 0x00, 0x00, 0x00};
const unsigned int  DVAP_REQ_FREQUENCY_LEN = 8U;

const unsigned char DVAP_RESP_FREQUENCY[] = {0x08, 0x00, 0x20, 0x02, 0x00, 0x00, 0x00, 0x00};
const unsigned int  DVAP_RESP_FREQUENCY_LEN = 8U;

const unsigned char DVAP_REQ_FREQLIMITS[] = {0x04, 0x20, 0x30, 0x02};
const unsigned int  DVAP_REQ_FREQLIMITS_LEN = 4U;

const unsigned char DVAP_RESP_FREQLIMITS[] = {0x0C, 0x00, 0x30, 0x02};
const unsigned int  DVAP_RESP_FREQLIMITS_LEN = 4U;

const unsigned char DVAP_REQ_START[] = {0x05, 0x00, 0x18, 0x00, 0x01};
const unsigned int  DVAP_REQ_START_LEN = 5U;

const unsigned char DVAP_RESP_START[] = {0x05, 0x00, 0x18, 0x00, 0x01};
const unsigned int  DVAP_RESP_START_LEN = 5U;

const unsigned char DVAP_REQ_STOP[] = {0x05, 0x00, 0x18, 0x00, 0x00};
const unsigned int  DVAP_REQ_STOP_LEN = 5U;

const unsigned char DVAP_RESP_STOP[] = {0x05, 0x00, 0x18, 0x00, 0x00};
const unsigned int  DVAP_RESP_STOP_LEN = 5U;

const unsigned char DVAP_HEADER[] = {0x2F, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
									 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
									 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
									 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
									 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const unsigned int  DVAP_HEADER_LEN = 47U;

const unsigned char DVAP_RESP_HEADER[] = {0x2F, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
										  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const unsigned int  DVAP_RESP_HEADER_LEN = 47U;

const unsigned char DVAP_RESP_PTT[] = {0x05, 0x20, 0x18, 0x01, 0x00};
const unsigned int  DVAP_RESP_PTT_LEN = 5U;

const unsigned char DVAP_DATA[] = {0x12, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const unsigned int  DVAP_DATA_LEN = 18U;

const unsigned char DVAP_STATUS[] = {0x07, 0x20, 0x90, 0x00, 0x00, 0x00, 0x00};
const unsigned int  DVAP_STATUS_LEN = 7U;

const unsigned char DVAP_ACK[] = {0x03, 0x60, 0x00};
const unsigned int  DVAP_ACK_LEN = 3U;

const unsigned int DVAP_HEADER_LENGTH = 2U;

const unsigned int MAX_RESPONSES = 20U;

const unsigned int BUFFER_LENGTH = 200U;

const unsigned char TAG_HEADER   = 0x00U;
const unsigned char TAG_DATA     = 0x01U;
const unsigned char TAG_DATA_END = 0x02U;

CDVAPController::CDVAPController(const wxString& port, unsigned int frequency, int power, int squelch) :
wxThread(wxTHREAD_JOINABLE),
m_serial(port, SERIAL_230400),
m_frequency(frequency),
m_power(power),
m_squelch(squelch),
m_space(0U),
m_ptt(false),
m_squelchOpen(false),
m_signal(0),
m_buffer(NULL),
m_streamId(0U),
m_framePos(0U),
m_seq(0U),
m_rxData(1000U),
m_txData(1000U),
m_stopped(false),
m_mutex()
{
	wxASSERT(!port.IsEmpty());
	wxASSERT(frequency >= 144000000U && frequency <= 148000000U);
	wxASSERT(power >= -12 && power <= 10);
	wxASSERT(squelch >= -128 && squelch <= -45);

	m_buffer = new unsigned char[BUFFER_LENGTH];
}

CDVAPController::~CDVAPController()
{
	delete[] m_buffer;
}

bool CDVAPController::open()
{
	bool res = m_serial.open();
	if (!res)
		return false;

	res = getName();
	if (!res) {
		m_serial.close();
		return false;
	}

	res = getFirmware();
	if (!res) {
		m_serial.close();
		return false;
	}

	res = getSerial();
	if (!res) {
		m_serial.close();
		return false;
	}

	res = setModulation();
	if (!res) {
		m_serial.close();
		return false;
	}

	res = setMode();
	if (!res) {
		m_serial.close();
		return false;
	}

	res = setSquelch();
	if (!res) {
		m_serial.close();
		return false;
	}

	res = setPower();
	if (!res) {
		m_serial.close();
		return false;
	}

	res = setFrequency();
	if (!res) {
		m_serial.close();
		return false;
	}

	res = start();
	if (!res) {
		m_serial.close();
		return false;
	}

	Create();
	SetPriority(100U);
	Run();

	return true;
}

void* CDVAPController::Entry()
{
	wxLogMessage(wxT("Starting DVAP Controller thread"));

	while (!m_stopped) {
		unsigned int length;
		RESP_TYPE type = getResponse(m_buffer, length);

		switch (type) {
			case RT_TIMEOUT:
				break;
			case RT_ERROR:
				wxLogMessage(wxT("Stopping DVAP Controller thread"));
				m_serial.close();
				return NULL;
			case RT_STATE: {
					m_signal      = int(m_buffer[4U]) - 256;
					m_squelchOpen = m_buffer[5U] == 0x01U;
					m_space       = m_buffer[6U];
				}
				break;
			case RT_PTT:
				m_ptt = m_buffer[4U] == 0x01U;	
				break;
			case RT_START:
				break;
			case RT_STOP:
				wxLogWarning(wxT("DVAP has stopped, restarting"));
				start();
				break;
			case RT_HEADER: {
					m_mutex.Lock();

					unsigned int space = m_rxData.freeSpace();
					if (space < 43U) {
						wxLogMessage(wxT("Out of space in the DVAP RX queue"));
					} else {
						unsigned char hdr[2U];
						hdr[0U] = TAG_HEADER;
						hdr[1U] = RADIO_HEADER_LENGTH_BYTES;
						m_rxData.addData(hdr, 2U);
						m_rxData.addData(m_buffer + 6U, RADIO_HEADER_LENGTH_BYTES);
					}

					m_mutex.Unlock();
				}
				break;
			case RT_HEADER_ACK:
				break;
			case RT_DATA: {
					m_mutex.Lock();

					unsigned int space = m_rxData.freeSpace();
					if (space < (length - 4U)) {
						wxLogMessage(wxT("Out of space in the DVAP RX queue"));
					} else {
						bool end = (m_buffer[4U] & 0x40U) == 0x40U;
						unsigned char hdr[2U];
						hdr[0U] = end ? TAG_DATA_END : TAG_DATA;
						hdr[1U] = length - 6U;
						m_rxData.addData(hdr, 2U);
						m_rxData.addData(m_buffer + 6U, length - 6U);
					}

					m_mutex.Unlock();
				}
				break;
			default:
				wxLogMessage(wxT("Unknown message"));
				CUtils::dump(wxT("Buffer dump"), m_buffer, length);
				break;
		}

		if (m_space > 0U) {
			m_mutex.Lock();
			if (!m_txData.isEmpty()) {
				unsigned char len;
				m_txData.getData(&len, 1U);

				unsigned char data[100U];
				m_txData.getData(data, len);
				m_mutex.Unlock();

				// CUtils::dump(wxT("Write"), data, len);

				int ret = m_serial.write(data, len);
				if (ret != int(len))
					wxLogWarning(wxT("Error when writing data to the modem"));

				m_space--;
			} else {
				m_mutex.Unlock();
			}
		}

		Sleep(5UL);
	}

	wxLogMessage(wxT("Stopping DVAP Controller thread"));

	stop();

	m_serial.close();

	return NULL;
}

bool CDVAPController::writePoll()
{
	wxMutexLocker locker(m_mutex);

	unsigned int space = m_txData.freeSpace();
	if (space < 4U) {
		wxLogMessage(wxT("Out of space in the DVAP TX queue"));
		return false;
	}

	unsigned char len = DVAP_ACK_LEN;
	m_txData.addData(&len, 1U);

	m_txData.addData(DVAP_ACK, DVAP_ACK_LEN);

	return true;
}

CHeaderData* CDVAPController::readHeader()
{
	wxMutexLocker locker(m_mutex);

	if (m_rxData.isEmpty())
		return NULL;

	unsigned char hdr[2U];
	m_rxData.getData(hdr, 2U);

	unsigned char header[100U];
	m_rxData.getData(header, hdr[1U]);

	if (hdr[0U] != TAG_HEADER)
		return NULL;

	return new CHeaderData(header, RADIO_HEADER_LENGTH_BYTES, false);
}

int CDVAPController::readData(unsigned char* data, unsigned int length, bool& end)
{
	wxMutexLocker locker(m_mutex);

	end = false;

	if (m_rxData.isEmpty())
		return -1;

	unsigned char hdr[2U];
	m_rxData.getData(hdr, 2U);

	if (hdr[0U] != TAG_DATA && hdr[0U] != TAG_DATA_END) {
		unsigned char buffer[100U];
		m_rxData.getData(buffer, hdr[1U]);
		return -1;
	}

	length = m_rxData.getData(data, hdr[1U]);

	end = hdr[0U] == TAG_DATA_END;

	return length;
}

bool CDVAPController::writeHeader(const CHeaderData& header)
{
	m_streamId++;

	unsigned char buffer[50U];

	::memcpy(buffer, DVAP_HEADER, DVAP_HEADER_LEN);

	wxUint16 sid = wxUINT16_SWAP_ON_BE(m_streamId);
	::memcpy(buffer + 2U, &sid, sizeof(wxUint16));

	buffer[4U] = 0x80U;
	buffer[5U] = 0U;

	::memset(buffer + 6U, ' ', RADIO_HEADER_LENGTH_BYTES);

	buffer[6U] = header.getFlag1();
	buffer[7U] = header.getFlag2();
	buffer[8U] = header.getFlag3();

	wxString rpt2 = header.getRptCall2();
	for (unsigned int i = 0U; i < rpt2.Len() && i < LONG_CALLSIGN_LENGTH; i++)
		buffer[i + 9U]  = rpt2.GetChar(i);

	wxString rpt1 = header.getRptCall1();
	for (unsigned int i = 0U; i < rpt1.Len() && i < LONG_CALLSIGN_LENGTH; i++)
		buffer[i + 17U] = rpt1.GetChar(i);

	wxString your = header.getYourCall();
	for (unsigned int i = 0U; i < your.Len() && i < LONG_CALLSIGN_LENGTH; i++)
		buffer[i + 25U] = your.GetChar(i);

	wxString my1 = header.getMyCall1();
	for (unsigned int i = 0U; i < my1.Len() && i < LONG_CALLSIGN_LENGTH; i++)
		buffer[i + 33U] = my1.GetChar(i);

	wxString my2 = header.getMyCall2();
	for (unsigned int i = 0U; i < my2.Len() && i < SHORT_CALLSIGN_LENGTH; i++)
		buffer[i + 41U] = my2.GetChar(i);

	CCCITTChecksumReverse cksum;
	cksum.update(buffer + 6U, RADIO_HEADER_LENGTH_BYTES - 2U);
	cksum.result(buffer + 45U);

	m_framePos = 0U;
	m_seq = 0U;

	wxMutexLocker locker(m_mutex);

	unsigned int space = m_txData.freeSpace();
	if (space < 48U) {
		wxLogMessage(wxT("Out of space in the DVAP TX queue"));
		return false;
	}

	unsigned char len = DVAP_HEADER_LEN;
	m_txData.addData(&len, 1U);

	m_txData.addData(buffer, DVAP_HEADER_LEN);

	return true;
}

bool CDVAPController::writeData(const unsigned char* data, unsigned int length, bool end)
{
	unsigned char buffer[20U];

	::memcpy(buffer + 0U, DVAP_DATA, DVAP_DATA_LEN);

	if (::memcmp(data + VOICE_FRAME_LENGTH_BYTES, DATA_SYNC_BYTES, DATA_FRAME_LENGTH_BYTES) == 0)
		m_framePos = 0U;

	wxUint16 sid = wxUINT16_SWAP_ON_BE(m_streamId);
	::memcpy(buffer + 2U, &sid, sizeof(wxUint16));

	buffer[4U] = m_framePos;
	buffer[5U] = m_seq;

	if (end)
		buffer[4U] |= 0x40U;

	::memcpy(buffer + 6U, data, DV_FRAME_LENGTH_BYTES);

	wxMutexLocker locker(m_mutex);

	unsigned int space = m_txData.freeSpace();
	if (space < 19U) {
		wxLogMessage(wxT("Out of space in the DVAP TX queue"));
		return false;
	}

	unsigned char len = DVAP_DATA_LEN;
	m_txData.addData(&len, 1U);

	m_txData.addData(buffer, DVAP_DATA_LEN);

	m_framePos++;
	m_seq++;

	return true;
}

void CDVAPController::close()
{
	m_stopped = true;

	Wait();
}

bool CDVAPController::hasSpace()
{
	wxMutexLocker locker(m_mutex);

	return m_txData.freeSpace() > 20U;
}

bool CDVAPController::getPTT() const
{
	return m_ptt;
}

bool CDVAPController::getSquelch() const
{
	return m_squelchOpen;
}

int CDVAPController::getSignal() const
{
	return m_signal;
}

bool CDVAPController::getName()
{
	int ret = m_serial.write(DVAP_REQ_NAME, DVAP_REQ_NAME_LEN);
	if (ret != int(DVAP_REQ_NAME_LEN)) {
		m_serial.close();
		return false;
	}

	unsigned int count = 0U;
	unsigned int length;
	RESP_TYPE resp;
	do {
		::wxMilliSleep(5UL);

		resp = getResponse(m_buffer, length);

		if (resp != RT_NAME) {
			count++;
			if (count >= MAX_RESPONSES) {
				wxLogError(wxT("The Dongle is not replying with its name"));
				return false;
			}
		}
	} while (resp != RT_NAME);

	bool cmp = ::memcmp(m_buffer, DVAP_RESP_NAME, length) == 0;
	if (!cmp) {
		wxLogError(wxT("The Dongle is not responding as a DVAP"));
		return false;
	}

	return true;
}

bool CDVAPController::getFirmware()
{
	int ret = m_serial.write(DVAP_REQ_FIRMWARE, DVAP_REQ_FIRMWARE_LEN);
	if (ret != int(DVAP_REQ_FIRMWARE_LEN)) {
		m_serial.close();
		return false;
	}

	unsigned int count = 0U;
	unsigned int length;
	RESP_TYPE resp;
	do {
		::wxMilliSleep(5UL);

		resp = getResponse(m_buffer, length);

		if (resp != RT_FIRMWARE) {
			count++;
			if (count >= MAX_RESPONSES) {
				wxLogError(wxT("The DVAP is not responding with its firmware version"));
				return false;
			}
		}
	} while (resp != RT_FIRMWARE);

	unsigned int version = m_buffer[6U] * 256U + m_buffer[5U];
	wxLogInfo(wxT("DVAP Firmware version: %u.%u"), version / 100U, version % 100U);

	return true;
}

bool CDVAPController::getSerial()
{
	int ret = m_serial.write(DVAP_REQ_SERIAL, DVAP_REQ_SERIAL_LEN);
	if (ret != int(DVAP_REQ_SERIAL_LEN)) {
		m_serial.close();
		return false;
	}

	unsigned int count = 0U;
	unsigned int length;
	RESP_TYPE resp;
	do {
		::wxMilliSleep(5UL);

		resp = getResponse(m_buffer, length);

		if (resp != RT_SERIAL) {
			count++;
			if (count >= MAX_RESPONSES) {
				wxLogError(wxT("The DVAP is not responding with its serial number"));
				return false;
			}
		}
	} while (resp != RT_SERIAL);

	wxString serial((char*)(m_buffer + 4U), wxConvLocal, length - 5U);
	wxLogInfo(wxT("DVAP Serial number: %s"), serial.c_str());

	return true;
}

bool CDVAPController::start()
{
	int ret = m_serial.write(DVAP_REQ_START, DVAP_REQ_START_LEN);
	if (ret != int(DVAP_REQ_START_LEN)) {
		m_serial.close();
		return false;
	}

	unsigned int count = 0U;
	unsigned int length;
	RESP_TYPE resp;
	do {
		::wxMilliSleep(5UL);

		resp = getResponse(m_buffer, length);

		if (resp != RT_START) {
			count++;
			if (count >= MAX_RESPONSES) {
				wxLogError(wxT("The DVAP is not responding to the start command"));
				return false;
			}
		}
	} while (resp != RT_START);

	return true;
}

bool CDVAPController::stop()
{
	int ret = m_serial.write(DVAP_REQ_STOP, DVAP_REQ_STOP_LEN);
	if (ret != int(DVAP_REQ_STOP_LEN)) {
		m_serial.close();
		return false;
	}

	unsigned int count = 0U;
	unsigned int length;
	RESP_TYPE resp;
	do {
		::wxMilliSleep(5UL);

		resp = getResponse(m_buffer, length);

		if (resp != RT_STOP) {
			count++;
			if (count >= MAX_RESPONSES) {
				wxLogError(wxT("The DVAP is not responding to the stop command"));
				return false;
			}
		}
	} while (resp != RT_STOP);

	return true;
}

bool CDVAPController::setModulation()
{
	int ret = m_serial.write(DVAP_REQ_MODULATION, DVAP_REQ_MODULATION_LEN);
	if (ret != int(DVAP_REQ_MODULATION_LEN)) {
		m_serial.close();
		return false;
	}

	unsigned int count = 0U;
	unsigned int length;
	RESP_TYPE resp;
	do {
		::wxMilliSleep(5UL);

		resp = getResponse(m_buffer, length);

		if (resp != RT_MODULATION) {
			count++;
			if (count >= MAX_RESPONSES) {
				wxLogError(wxT("The DVAP is not responding to the modulation command"));
				return false;
			}
		}
	} while (resp != RT_MODULATION);

	return true;
}

bool CDVAPController::setMode()
{
	int ret = m_serial.write(DVAP_REQ_MODE, DVAP_REQ_MODE_LEN);
	if (ret != int(DVAP_REQ_MODE_LEN)) {
		m_serial.close();
		return false;
	}

	unsigned int count = 0U;
	unsigned int length;
	RESP_TYPE resp;
	do {
		::wxMilliSleep(5UL);

		resp = getResponse(m_buffer, length);

		if (resp != RT_MODE) {
			count++;
			if (count >= MAX_RESPONSES) {
				wxLogError(wxT("The DVAP is not responding to the mode command"));
				return false;
			}
		}
	} while (resp != RT_MODE);

	return true;
}

bool CDVAPController::setSquelch()
{
	unsigned char buffer[10U];

	::memcpy(buffer, DVAP_REQ_SQUELCH, DVAP_REQ_SQUELCH_LEN);

	::memcpy(buffer + 4U, &m_squelch, sizeof(wxInt8));

	int ret = m_serial.write(buffer, DVAP_REQ_SQUELCH_LEN);
	if (ret != int(DVAP_REQ_SQUELCH_LEN)) {
		m_serial.close();
		return false;
	}

	unsigned int count = 0U;
	unsigned int length;
	RESP_TYPE resp;
	do {
		::wxMilliSleep(5UL);

		resp = getResponse(m_buffer, length);

		if (resp != RT_SQUELCH) {
			count++;
			if (count >= MAX_RESPONSES) {
				wxLogError(wxT("The DVAP is not responding to the squelch command"));
				return false;
			}
		}
	} while (resp != RT_SQUELCH);

	return true;
}

bool CDVAPController::setPower()
{
	unsigned char buffer[10U];

	::memcpy(buffer, DVAP_REQ_POWER, DVAP_REQ_POWER_LEN);

	wxInt16 power = wxINT16_SWAP_ON_BE(m_power);
	::memcpy(buffer + 4U, &power, sizeof(wxInt16));

	int ret = m_serial.write(buffer, DVAP_REQ_POWER_LEN);
	if (ret != int(DVAP_REQ_POWER_LEN)) {
		m_serial.close();
		return false;
	}

	unsigned int count = 0U;
	unsigned int length;
	RESP_TYPE resp;
	do {
		::wxMilliSleep(5UL);

		resp = getResponse(m_buffer, length);

		if (resp != RT_POWER) {
			count++;
			if (count >= MAX_RESPONSES) {
				wxLogError(wxT("The DVAP is not responding to the power command"));
				return false;
			}
		}
	} while (resp != RT_POWER);

	return true;
}

bool CDVAPController::setFrequency()
{
	unsigned char buffer[10U];

	int ret = m_serial.write(DVAP_REQ_FREQLIMITS, DVAP_REQ_FREQLIMITS_LEN);
	if (ret != int(DVAP_REQ_FREQLIMITS_LEN)) {
		m_serial.close();
		return false;
	}

	unsigned int count = 0U;
	unsigned int length;
	RESP_TYPE resp;
	do {
		::wxMilliSleep(5UL);

		resp = getResponse(m_buffer, length);

		if (resp != RT_FREQLIMITS) {
			count++;
			if (count >= MAX_RESPONSES) {
				wxLogError(wxT("The DVAP is not responding to the frequency limits command"));
				return false;
			}
		}
	} while (resp != RT_FREQLIMITS);

	wxUint32* pFreq1 = (wxUint32*)(m_buffer + 4U);
	wxUint32* pFreq2 = (wxUint32*)(m_buffer + 8U);

	wxUint32 lower = wxUINT32_SWAP_ON_BE(*pFreq1);
	wxUint32 upper = wxUINT32_SWAP_ON_BE(*pFreq2);

	wxLogInfo(wxT("DVAP frequency limits are %u Hz to %u Hz"), lower, upper);

	if (m_frequency < lower || m_frequency > upper) {
		wxLogError(wxT("The required frequency is out of the range of the DVAP hardware"));
		m_serial.close();
		return false;
	}

	::memcpy(buffer, DVAP_REQ_FREQUENCY, DVAP_REQ_FREQUENCY_LEN);

	wxUint32 frequency = wxUINT32_SWAP_ON_BE(m_frequency);
	::memcpy(buffer + 4U, &frequency, sizeof(wxUint32));

	ret = m_serial.write(buffer, DVAP_REQ_FREQUENCY_LEN);
	if (ret != int(DVAP_REQ_FREQUENCY_LEN)) {
		m_serial.close();
		return false;
	}

	count = 0U;
	do {
		::wxMilliSleep(5UL);

		resp = getResponse(m_buffer, length);

		if (resp != RT_FREQUENCY) {
			count++;
			if (count >= MAX_RESPONSES) {
				wxLogError(wxT("The DVAP is not responding to the frequency command"));
				return false;
			}
		}
	} while (resp != RT_FREQUENCY);

	return true;
}

RESP_TYPE CDVAPController::getResponse(unsigned char *buffer, unsigned int& length)
{
	int ret = m_serial.read(buffer, DVAP_HEADER_LENGTH);
	if (ret == 0)
		return RT_TIMEOUT;
	if (ret != int(DVAP_HEADER_LENGTH))
		return RT_ERROR;

	length = buffer[0U] + (buffer[1U] & 0x1FU) * 256U;

	// Check for silliness
	if (length > 50U) {
		resync();
		return RT_TIMEOUT;
	}

	unsigned int offset = DVAP_HEADER_LENGTH;

	while (offset < length) {
		int ret = m_serial.read(buffer + offset, length - offset);
		if (ret < 0)
			return RT_ERROR;
		if (ret > 0)
			offset += ret;
		if (ret == 0)
			Sleep(5UL);
	}

	// CUtils::dump(wxT("Received"), buffer, length);

	if (::memcmp(buffer, DVAP_STATUS, 4U) == 0)
		return RT_STATE;
	else if (::memcmp(buffer, DVAP_DATA, 2U) == 0)
		return RT_DATA;
	else if (::memcmp(buffer, DVAP_HEADER, 2U) == 0)
		return RT_HEADER;
	else if (::memcmp(buffer, DVAP_RESP_HEADER, 2U) == 0)
		return RT_HEADER_ACK;
	else if (::memcmp(buffer, DVAP_RESP_PTT, 4U) == 0)
		return RT_PTT;
	else if (::memcmp(buffer, DVAP_ACK, DVAP_ACK_LEN) == 0)
		return RT_ACK;
	else if (::memcmp(buffer, DVAP_RESP_START, DVAP_RESP_START_LEN) == 0)
		return RT_START;
	else if (::memcmp(buffer, DVAP_RESP_STOP, DVAP_RESP_STOP_LEN) == 0)
		return RT_STOP;
	else if (::memcmp(buffer, DVAP_RESP_NAME, 4U) == 0)
		return RT_NAME;
	else if (::memcmp(buffer + 1U, DVAP_RESP_SERIAL + 1U, 3U) == 0)
		return RT_SERIAL;
	else if (::memcmp(buffer, DVAP_RESP_FIRMWARE, 5U) == 0)
		return RT_FIRMWARE;
	else if (::memcmp(buffer, DVAP_RESP_FREQUENCY, 4U) == 0)
		return RT_FREQUENCY;
	else if (::memcmp(buffer, DVAP_RESP_FREQLIMITS, 4U) == 0)
		return RT_FREQLIMITS;
	else if (::memcmp(buffer, DVAP_RESP_MODULATION, DVAP_RESP_MODULATION_LEN) == 0)
		return RT_MODULATION;
	else if (::memcmp(buffer, DVAP_RESP_MODE, DVAP_RESP_MODE_LEN) == 0)
		return RT_MODE;
	else if (::memcmp(buffer, DVAP_RESP_POWER, 4U) == 0)
		return RT_POWER;
	else if (::memcmp(buffer, DVAP_RESP_SQUELCH, 4U) == 0)
		return RT_SQUELCH;
	else {
		resync();
		return RT_TIMEOUT;
	}
}

void CDVAPController::resync()
{
	wxLogWarning(wxT("Resynchronising the DVAP data stream"));

	unsigned char data[DVAP_STATUS_LEN];
	::memset(data, 0x00U, DVAP_STATUS_LEN);

	while (::memcmp(data, DVAP_STATUS, 4U) != 0) {
		unsigned char c;
		int n = m_serial.read(&c, 1U);
		if (n > 0) {
			data[0U] = data[1U];
			data[1U] = data[2U];
			data[2U] = data[3U];
			data[3U] = data[4U];
			data[4U] = data[5U];
			data[5U] = data[6U];
			data[6U] = c;

			CUtils::dump(wxT("Resync buffer"), data, DVAP_STATUS_LEN);
		}
	}

	wxLogMessage(wxT("End resynchronising"));
}
