#include "SudokuPuzzle.h"
#include <Windows.h>

SudokuPuzzle::~SudokuPuzzle(void)
{
}

void SudokuPuzzle::Solve(char filenameIn[])
{
	//Importing data into the puzzle from the text file
	ImportValues(filenameIn);

	LARGE_INTEGER start, end, frequency;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);

	// Solve the puzzle
	bool solved = true;
	int blockIndex[2];
	int passes = 0;

	do {
		//reset solved value for new pass
		solved = true;
		++passes;

		for (int row = 0; row < m_puzzleSize; ++row) {

			for (int column = 0; column < m_puzzleSize; ++column) {
				//Is the value a given?
				if (!m_rows[row].getCell(column)->isGiven()) {
					//Does the value equal zero?
					if (m_rows[row].getCell(column)->getValue() == 0) {
						solved = false; // This puzzle is therefore not solved

						//Reduce candidate list
						getBlockAndIndexFromCoords(row, column, &blockIndex[0]);

						for (int i = 0; i < 9; ++i) {
							//Is this cell equal to 0?
							//Row context
							if (!m_rows[row].getCell(i)->getValue() == 0) {
								//If not, remove this value from the candidate list
								m_rows[row].getCell(column)->
									removeCandidate(m_rows[row].getCell(i)->getValue());
							}
							//Column context
							if (!m_columns[column].getCell(i)->getValue() == 0) {
								m_columns[column].getCell(row)->
									removeCandidate(m_columns[column].getCell(i)->getValue());
							}
							//Block context
							if (!m_blocks[blockIndex[0]].getCell(i)->getValue() == 0) {
								m_blocks[blockIndex[0]].getCell(blockIndex[1])->
									removeCandidate(m_blocks[blockIndex[0]].getCell(i)->getValue());
							}
						}

						//If size of candidate list is 1, value of cell is set to the 0th index of the list
						if (m_rows[row].getCell(column)->getCandiListSize() == 1) {
							m_rows[row].getCell(column)->setValue(m_rows[row].getCell(column)->getCandidateAt(0));
						}

					}
				}
			}

		}

	} while (!solved);

	QueryPerformanceCounter(&end);
	float time = (end.QuadPart - start.QuadPart) / (static_cast<float> (frequency.QuadPart));
	//Printing stats
	cout << "Completed in: " << endl;
	cout << time << " seconds" << endl;
	cout << passes << " passes" << endl << endl;
	Output();  // Output the solved puzzle
}

void SudokuPuzzle::ImportValues(char fileNameIn[])
{
	ifstream fin(fileNameIn);

	int blockIndex[2];

	//Importing into rows
	for (int row = 0; row < m_puzzleSize; ++row) {
		for (int column = 0; column < m_puzzleSize; ++column) {
			int currentValue;
			bool currentGiven = true;
			fin >> currentValue;

			//if the value is zero, it is blank and was not given by the puzzle
			if (currentValue == 0) {
				currentGiven = false;
			}

			//Create cell in rows
			m_rows[row].setCell(column, new Cell(currentValue, currentGiven));
			//Copy into columns
			m_columns[column].setCell(row, m_rows[row].getCell(column));
			//Copy into blocks
			getBlockAndIndexFromCoords(row, column, &blockIndex[0]);
			m_blocks[blockIndex[0]].setCell(blockIndex[1], m_rows[row].getCell(column));
		}
	}
}

void SudokuPuzzle::printPuzzle() const
{
	cout.clear();//Clears the screen

	//Print rows
	cout << "Rows" << endl;

	for (int row = 0; row < m_puzzleSize; ++row) {
		for (int column = 0; column < m_puzzleSize; ++column) {
			cout << m_rows[row].getCell(column)->getValue() << " ";
		}

		cout << endl;
	}
	
	//Print Columns
	cout << endl;
	cout << "Columns" << endl;

	for (int column = 0; column < m_puzzleSize; ++column) {
		for (int row = 0; row < m_puzzleSize; ++row) {
			cout << m_columns[row].getCell(column)->getValue() << " ";
		}

		cout << endl;
	}

	//Print Blocks
	cout << endl;
	cout << "Blocks" << endl;

	int blockIndex[2];

	for (int row = 0; row < m_puzzleSize; ++row) {
		for (int column = 0; column < m_puzzleSize; ++column) {
			getBlockAndIndexFromCoords(row, column, &blockIndex[0]);
			cout << m_blocks[blockIndex[0]].getCell(blockIndex[1])->getValue() << " ";
		}

		cout << endl;
	}
	
}

void SudokuPuzzle::getBlockAndIndexFromCoords(const int row, const int column, int* outBlockandIndex) const
{
	int blockRow = row / 3;
	int blockColumn = column / 3;
	int blockIndex = 0;
	int blockRowValueIndex = 0;
	int blockColumnValueIndex = 0;
	int blockValueIndex = 0;

	//Caluclating row value
	if (blockRow == 0) {
		blockIndex = blockColumn;
		blockRowValueIndex = row;
	}
	else if (blockRow == 1) {
		blockIndex = 3 + blockColumn;
		blockRowValueIndex = row - 3;
	}
	else {
		blockIndex = 6 + blockColumn;
		blockRowValueIndex = row - 6;
	}

	//Calculating column value
	if (blockColumn == 0) {
		blockColumnValueIndex = column;
	}
	else if (blockColumn == 1) {
		blockColumnValueIndex = column - 3;
	}
	else {
		blockColumnValueIndex = column - 6;
	}

	blockValueIndex = blockColumnValueIndex + (blockRowValueIndex * 3);

	outBlockandIndex[0] = blockIndex;
	outBlockandIndex[1] = blockValueIndex;
}

// This is an example of how you may output the solved puzzle
void SudokuPuzzle::Output() const
{
	ofstream fout("sudoku_solution.txt"); // DO NOT CHANGE THE NAME OF THIS FILE
	if (fout.is_open())
	{
		for (int y = 0; y < 9; ++y)
		{
			for (int x = 0; x < 9; ++x)
			{
					fout << m_rows[y].getCell(x)->getValue() << " ";
			}

			fout << endl;
		}
		fout.close();
	}
}
