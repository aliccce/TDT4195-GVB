#include <iostream>
#include <fstream>
#include "readBoard.hpp"
#include <stdio.h>

using namespace std;


int readFile(Board *board, char *path)
{
	string line;
	ifstream file (path);
	size_t index = 0;

	if (file.is_open())
	{
		while (getline(file, line))
		{
			Shape *shape = new Shape;
			parseLine(shape, line);
			board->addPiece(shape);
			printf("%d", index++);
		}

		file.close();
		return 1;
	}

	else
	{
		cout << "Unable to open file.";
	}

	return 0;
}



void parseLine(Shape *shape, string line)
{
	int counter = 0;
	int index;
	int begin = 0;
	char sep = ' ';

	for (index = 0; index < line.length(); index++)
	{
		if ((char) line[index] == sep) 
		{
			switch (counter)
			{
			case 0:
				/* SET ROW */
				shape->setRow(stoi(line.substr(begin, index - begin)));
				begin = index + 1;
				counter++;
				break;

			case 1:
				/* SET COLUMN */
				shape->setCol(stoi(line.substr(begin, index - begin)));
				begin = index + 1;
				counter++;
				break;

			case 2:
				/* SET TYPE */
				shape->setType(stoi(line.substr(begin, index - begin)));
				begin = index + 1;
				counter++;
				break;

			case 3:
				/* SET CENTER X */
				shape->setCenterX(stof(line.substr(begin, index - begin)));
				begin = index + 1;
				counter++;
				break;
			case 4:
				/* SET CENTER Y */
				shape->setCenterY(stof(line.substr(begin, index - begin)));
				begin = index + 1;
				counter++;
				break;
			}


		}
		

	}

}