#pragma once
#include "CellGroup.h"
#include "Cell.h"
#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

class SudokuPuzzle
{
public:
	SudokuPuzzle(void) : m_puzzleSize(9), m_blockSize(m_puzzleSize / 3) {}
	~SudokuPuzzle(void);

	void Solve(char filenameIn[]);

private:
	void Output() const;
	void ImportValues(char fileNameIn[]);
	void printPuzzle() const;
	void getBlockAndIndexFromCoords(const int row, const int column, int* outBlockandIndex) const;

	CellGroup m_rows[9];
	CellGroup m_columns[9];
	CellGroup m_blocks[9];

	int m_puzzleSize;
	int m_blockSize = m_puzzleSize / 3;
};

