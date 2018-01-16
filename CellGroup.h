#pragma once
#include "Cell.h"
class CellGroup
{
public:
	CellGroup();
	~CellGroup();

	void setCell(int index, Cell *cell);
	Cell* getCell(int index) const;

private:
	Cell* m_cells[9];
};

