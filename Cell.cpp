#include "Cell.h"

Cell::Cell(const int p_value, const bool p_given)
{
	m_value = p_value;
	m_given = p_given;
	//Populating candidate list
	for (int i = 1; i <= 9; ++i) {
		m_candidateList.push_back(i);
	}
}

Cell::~Cell()
{
}

Cell::Cell()
{
	m_value = 0;
	m_given = false;
	//Populating candidate list
	for (int i = 1; i <= 9; ++i) {
		m_candidateList.push_back(i);
	}
}

int Cell::getValue() const
{
	return m_value;
}

bool Cell::isGiven() const
{
	return m_given;
}

int Cell::getCandiListSize() const
{
	return m_candidateList.size();
}

int Cell::getCandidateAt(int index) const
{
	return m_candidateList[index];
}

void Cell::setValue(int newValue)
{
	m_value = newValue;
}

void Cell::setGiven(bool newValue)
{
	m_given = newValue;
}

void Cell::addCandidate(int newCandidate)
{
	bool isDuplicate = false;

	//Checking if item already exists in the list
	for (size_t i = 0; i < m_candidateList.size(); ++i) {
		if (m_candidateList[i] == newCandidate) {
			isDuplicate = true;
		}
	}

	if (!isDuplicate) {
		m_candidateList.push_back(newCandidate);
	}
}

void Cell::removeCandidate(int removalCandidate)
{
	//Find the position of the element to remove and reomve it from that position
	for (size_t i = 0; i < m_candidateList.size(); ++i) {
		if (m_candidateList[i] == removalCandidate) {
			m_candidateList.erase(m_candidateList.begin() + i);
		}
	}
}
