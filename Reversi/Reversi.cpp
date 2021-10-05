#include "Reversi.h"
#include "KeyControl.h"
#include "Display.h"
#include "WordColor.h"
#include <string>
#define WHITE 1
#define BLACK 2

Reversi::Reversi()
{
	_isAnimation = 1;
	isMusic = 0;
	ifAIEnabled = 0;
	currentTerm = 0;
	_ifDeleteBoards = 0;
	_ifPlay = 1;
	_ateChessCount[0] = 2;
	_ateChessCount[1] = 2;
	_round = 0;
	_handlePlayer = 2;
	_colorFlag = 1;
}


Reversi::~Reversi()
{
}

void Reversi::initialBoard()
{
	_isAnimation = 1;
	isMusic = 0;
	ifAIEnabled = 0;
	_ifPlay = 1;
	_ateChessCount[0] = 0;
	_ateChessCount[1] = 0;
	_round = 0;
	_handlePlayer = 2;
	_colorFlag = 1;
	Key::_playerCusor = posXY{ 4,4 };
	WordColor::setWordColor(WordColor::White, 1, WordColor::Violet, 1);
	Draw::drawChess(posXY{ 4,4 }, 1);
	WordColor::defaultColor();

	_board.clear();
	for (int i = 0; i < 8; i++) {
		vector<int> boardLayer;
		vector<vector<struct posXY> > chessLayer;
		for (int j = 0; j < 8; j++) {
			boardLayer.push_back(0);
			vector<struct posXY> Temp;
			chessLayer.push_back(Temp);
		}
		_board.push_back(boardLayer);
		_ateChesses.push_back(chessLayer);
	}
	_board[3][3] = WHITE;
	_board[4][4] = WHITE;
	_board[3][4] = BLACK;
	_board[4][3] = BLACK;
	this->_round = 0;
	for (int i = 0; i < _board.size(); i++) {
		for (int j = 0; j < _board[i].size(); j++) {
			Draw::drawChess(posXY{ j, i }, _board[j][i]);
		}
	}
	_boards.push_back(_board);
	_hadlePlayerRecord.push_back(BLACK);
}

bool Reversi::positionCheck(struct posXY pos)
{
	_ateChesses[pos.posY][pos.posX].clear();
	if (_board[pos.posY][pos.posX])
		return 0;
	bool ifAvailible = 0;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (i == 0 && j == 0) {
				continue;
				//_ateChessEstimate[pos.posY][pos.posX] = 0;				
			}
			if (!(pos.posY + i >= 8 || pos.posY + i < 0 || pos.posX + j >= 8 || pos.posX + j < 0)) { //position in chess board
				//_ateChessEstimate[pos.posY + i][pos.posX + j] = 0;
				//_ateChesses[pos.posY][pos.posX].clear();
				if (_board[pos.posY + i][pos.posX + j] == _handlePlayer) //if the nearby chest is mine >> unavailible
					continue;
				else if (_board[pos.posY + i][pos.posX + j] == 0) //if there's no chest nearby >> unavailible
					continue;
				int k = 1;
				bool flag = 0;
				while (!(pos.posX + k * j >= 8 || pos.posX + k * j < 0 || pos.posY + k * i >= 8 || pos.posY + k * i < 0)) {
					if (_board[pos.posY + k * i][pos.posX + k * j] == 0)
						break; //exit while, no mine chest, no eat.
					else if (_board[pos.posY + k * i][pos.posX + k * j] == 3 - _handlePlayer) { //it's enemy
						flag = 1;
						k++;
					}
					else if (_board[pos.posY + k * i][pos.posX + k * j] == _handlePlayer) { //it's mine
						if (!flag)
							break;
						//_ateChessEstimate[pos.posY + i][pos.posX + j] += k - 1;
						for (int h = 0; h < k; h++) {
							_ateChesses[pos.posY][pos.posX].push_back(posXY{ pos.posX + h * j , pos.posY + h * i });
						}
						
						ifAvailible = 1;
						break;
					}
				}
				continue;
			}
		}
	}
	return ifAvailible;
}

void Reversi::gameOver(int winner, bool & ifPlay)
{
	canvas OverBoard;
	WordColor::setWordColor(WordColor::White, 1, WordColor::Red, 0);
	string OverBoardContent[] = {
		"　　　　　　　　　　　　",
		"　《《　遊戲結束　》》　",
		"　　　　　　　　　　　　",
		"　　棋勝利，再來一局？　",
		"　　　　　　　　　　　　",
		"　　　好Ｒ　　別啦　　　",
		"　　　　　　　　　　　　"
	};
	OverBoard.boardContent = OverBoardContent;
	OverBoard.drawBoard(posXY{ BOARD_X + 7,0 }, 7);

	canvas WinPlayer;
	WordColor::setWordColor(WordColor::White, 1, WordColor::Red, 0);
	string WinPlayerName;
	if (winner == BLACK)
		WinPlayerName = "黑";
	else if (winner == WHITE)
		WinPlayerName = "白";
	else
		WinPlayerName = "平手也好";
	WinPlayer.boardContent = &WinPlayerName;
	WinPlayer.drawBoard(posXY{ BOARD_X + 9,3 }, 1);

	//Cusor
	vector<struct posXY> positions;
	positions.push_back(posXY{ BOARD_X + 13,5 });
	positions.push_back(posXY{ BOARD_X + 21,5 });
	vector<string> buttonContents;
	buttonContents.push_back("好Ｒ");
	buttonContents.push_back("別啦");
	vector <bool> idensities = { true,true, 0,1 };
	MColor::MenuColor menuColors = {
		WordColor::Bule,
		WordColor::White,
		WordColor::Red,
		WordColor::White,
		idensities
	};
	//menuColors.cusor = WordColor::Bule;
	//std::vector<bool> iii = { 1, 1, 1, 1 };
	//MenuColor menuColors(WordColor::Bule, WordColor::White, WordColor::Red, WordColor::White);
	int ifRestart = Key::menuControl(Key::getKey(), positions, buttonContents, 2, 0, menuColors);
	if (ifRestart == 0)
		this->_ifPlay = 0;
	else
		exit(0);
}

void Reversi::loadBoard(int term)
{
	if (term < 0 || term >= _boards.size())
		return;
	_board = _boards[term];
	_handlePlayer = _hadlePlayerRecord[term];
	Draw::drawAllChess(*this);
	canvas playerTermBoard;
	string player;
	if (_handlePlayer == 1) {
		WordColor::setWordColor(WordColor::Black, 1, WordColor::White, 1);
		player = "白方";
	}
	else {
		WordColor::setWordColor(WordColor::White, 1, WordColor::Black, 1);
		player = "黑方";
	}
	playerTermBoard.boardContent = &player;
	playerTermBoard.drawBoard(posXY{ BOARD_X + 18,3 }, 1);
	WordColor::defaultColor();
}

