#include <vector>
#include "shapes.hpp"


class Board {

public:
	float topLeft;
	float topRight;
	unsigned int n;
	unsigned int m;
	unsigned int boardId;
	std::vector<Shape*> pieces;

	Board(unsigned int n, unsigned int m);
	unsigned int createBoard();
	void addPiece(Shape* piece) { this->pieces.push_back(piece); }
};
