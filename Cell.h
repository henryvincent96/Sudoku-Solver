#pragma once
#include <vector>
class Cell
{
public:
	Cell(const int p_value, const bool p_given);
	~Cell();

	Cell();

	//Accessors
	int getValue() const;
	bool isGiven() const;
	int getCandiListSize() const;
	int getCandidateAt(int index) const;

	//Mutators
	void setValue(int newValue);
	void setGiven(bool newValue);
	void addCandidate(int newCandidate);
	void removeCandidate(int removalCandidate);

private:
	int m_value;
	bool m_given;
	std::vector<int> m_candidateList;
};