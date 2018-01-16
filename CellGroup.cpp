#include "CellGroup.h"



CellGroup::CellGroup()
{
	for (int i = 0; i < 9; ++i) {
		m_cells[i] = new Cell();
	}
}


CellGroup::~CellGroup()
{
}

void CellGroup::setCell(int index, Cell * cell)
{
	m_cells[index] = cell;
}

Cell * CellGroup::getCell(int index) const
{
	return m_cells[index];
}
