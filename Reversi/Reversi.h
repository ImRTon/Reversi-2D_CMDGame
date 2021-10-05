#pragma once
#include <vector>
using std::vector;

struct posXY
{
	int posX;
	int posY;
};

struct chessRecord {
	struct posXY chessPos;
	int chessType;
};

class Reversi
{
public:
	Reversi();
	~Reversi();

	void initialBoard();
	bool positionCheck(struct posXY);
	void gameOver(int winner, bool & ifPlay);
	bool _ifPlay;
	void loadBoard(int term);
	bool _ifDeleteBoards;
	int currentTerm;

	bool _isAnimation;
	bool isMusic;
	int ifAIEnabled;
	int _ateChessCount[2]; //
	int _round; //initial as 0.
	int _handlePlayer; //whose player's round. 0 as none, 1 as white, 2 as black
	vector<int> _hadlePlayerRecord;
	bool _colorFlag; //if player0 is white, than
	vector<vector<int> > _board; //0 as none, 1 as white, 2 as black
	vector<vector<vector<int> > > _boards; //play boards
	int _ateChessEstimate[8][8];
	vector<vector<vector<struct posXY> > > _ateChesses;
	vector<struct chessRecord> chessRecords;
};

