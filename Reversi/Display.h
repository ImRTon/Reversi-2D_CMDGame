#pragma once
#include <string>
using std::string;

#define BOARD_X 16
#define BOARD_Y 6

struct posXY;
class Reversi;

class canvas
{
public:
	canvas();
	~canvas();

	void drawBoard(struct posXY, int lengthRow);

	string* boardContent;
	string _canvas;
};

namespace Draw {
	void drawChess(posXY chessPos, int charType);
	void drawAllChess(Reversi & reversi);
	void displayScore(Reversi & reversi, bool& ifPlay);
	void displayString(posXY pos, string content);
	void drawMenu(Reversi & reversi);
	void displayRecord(Reversi & reversi, struct posXY pos, int chessType);
}