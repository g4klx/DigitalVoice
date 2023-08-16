/*
 *	Copyright (C) 2009 Jonathan Naylor, G4KLX
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

#include "PatternMatcher.h"

#include <wx/wx.h>

CPatternMatcher::CPatternMatcher(unsigned int length, const bool* pattern, unsigned int count) :
m_patternLength(0U),
m_pattern(NULL),
m_dataLength(0U),
m_data(NULL)
{
	wxASSERT(length > 0U);
	wxASSERT(count > 0U);

	m_patternLength = length * count;

	m_pattern = new bool[m_patternLength];
	m_data    = new bool[m_patternLength];

	unsigned int n = m_patternLength - 1U;

	for (unsigned int i = 0U; i < count; i++)
		for (unsigned int j = 0U; j < length; j++)
			m_pattern[n--] = pattern[j];
}

CPatternMatcher::~CPatternMatcher()
{
	delete[] m_pattern;
	delete[] m_data;
}

bool CPatternMatcher::add(bool bit)
{
	for (unsigned int i = m_patternLength - 1U; i >= 1U; i--)
		m_data[i] = m_data[i - 1U];
	m_data[0] = bit;

	if (m_dataLength < m_patternLength)
		m_dataLength++;

	if (m_dataLength != m_patternLength)
		return false;

	for (unsigned int i = 0U; i < m_patternLength; i++)
		if (m_pattern[i] != m_data[i])
			return false;

	return true;
}

void CPatternMatcher::reset()
{
	m_dataLength = 0U;
}
