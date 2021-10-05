#include <iostream>
#include <Windows.h>
#include <sstream>
#include "Display.h"
#include "KeyControl.h"
#include "WordColor.h"
#pragma comment(lib, "winmm.lib")
using namespace std;

#define WHITE 1
#define BLACK 2
#define AI_RESPONSE_TIME 1000

void drawChessBoard() {
	canvas chessBoard;
	string boardTemplate[] = {
		"¡@  ¢י¡@¢ך¡@¢כ¡@¢ל¡@¢ם¡@¢מ¡@¢ן¡@¢נ¡@¡@",
		"¡@שÝשששששששÞשששששששÞשששששששÞשששששששÞשששששששÞשששששששÞשששששששÞשששששששß¡@",
		"¢°שר   שר   שר   שר   שר   שר   שר   שר   שר ¢°",
		"¡@שאשששששששבשששששששבשששששששבשששששששבשששששששבשששששששבשששששששבשששששששג¡@",
		"¢±שר   שר   שר   שר   שר   שר   שר   שר   שר ¢±",
		"¡@שאשששששששבשששששששבשששששששבשששששששבשששששששבשששששששבשששששששבשששששששג¡@",
		"¢²שר   שר   שר   שר   שר   שר   שר   שר   שר ¢²",
		"¡@שאשששששששבשששששששבשששששששבשששששששבשששששששבשששששששבשששששששבשששששששג¡@",
		"¢³שר   שר   שר   שר   שר   שר   שר   שר   שר ¢³",
		"¡@שאשששששששבשששששששבשששששששבשששששששבשששששששבשששששששבשששששששבשששששששג¡@",
		"¢´שר   שר   שר   שר   שר   שר   שר   שר   שר ¢´",
		"¡@שאשששששששבשששששששבשששששששבשששששששבשששששששבשששששששבשששששששבשששששששג¡@",
		"¢µשר   שר   שר   שר   שר   שר   שר   שר   שר ¢µ",
		"¡@שאשששששששבשששששששבשששששששבשששששששבשששששששבשששששששבשששששששבשששששששג¡@",
		"¢¶שר   שר   שר   שר   שר   שר   שר   שר   שר ¢¶",
		"¡@שאשששששששבשששששששבשששששששבשששששששבשששששששבשששששששבשששששששבשששששששג¡@",
		"¢·שר   שר   שר   שר   שר   שר   שר   שר   שר ¢·",
		"¡@שדשששששששהשששששששהשששששששהשששששששהשששששששהשששששששהשששששששהשששששששו¡@",
		"¡@  ¢י¡@¢ך¡@¢כ¡@¢ל¡@¢ם¡@¢מ¡@¢ן¡@¢נ¡@¡@"
	};
	chessBoard.boardContent = boardTemplate;
	chessBoard.drawBoard(posXY{ BOARD_X,BOARD_Y }, 19);

	canvas playerTermBoard;
	WordColor::setWordColor(WordColor::White, 1, WordColor::Yellow, 0);
	string PlayerTerm[] = {
		"¡@¡@¡@¡@¡@¡@¡@¡@¡@",
		"¡@²{¦b¥ׁ¡@¡@₪U´ׁ¡@",
		"¡@¡@¡@¡@¡@¡@¡@¡@¡@"
	};
	playerTermBoard.boardContent = PlayerTerm;
	playerTermBoard.drawBoard(posXY{ BOARD_X + 10,2 }, 3);

	canvas playerScore;
	WordColor::setWordColor(WordColor::White, 1, WordColor::Bule, 0);
	string playerScored[] = {
		"¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@",
		"¡@¡@¡@¡@¡@¡@¡@¡@°O₪ְ×O¡@¡´¡@¡@¡@¡@¡@¡@",
		"¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@¡@"
	};
	playerTermBoard.boardContent = playerScored;
	playerTermBoard.drawBoard(posXY{ BOARD_X,BOARD_Y + 20 }, 3);
	canvas playerScoreBlack;
	WordColor::setWordColor(WordColor::Black, 1, WordColor::Bule, 0);
	string playerScoredBlack = "¡´";
	playerScoreBlack.boardContent = &playerScoredBlack;
	playerScoreBlack.drawBoard(posXY{ BOARD_X + 12,BOARD_Y + 21 }, 1);
	WordColor::defaultColor();

	WordColor::setWordColor(WordColor::Cyan, 1, WordColor::Gray, 0);
	for (int i = 0; i < 19; i++) {
		Draw::displayString(posXY{ BOARD_X + 6 + 34, BOARD_Y + i }, "¡@¡@¡@¡@¡@¡@¡@¡@¡@");
	}
	WordColor::setWordColor(WordColor::White, 1, WordColor::Gray, 0);
	Draw::displayString(posXY{ BOARD_X + 29, BOARD_Y - 2 }, " AI Off ");
	WordColor::defaultColor();
	Draw::displayString(posXY{ BOARD_X + 40, BOARD_Y + 20 }, "¢ו¢ֿ¢ב¢ׂ¡@¡צ¡פ¡ק¡ץ¡@₪ט¦V");
	Draw::displayString(posXY{ BOARD_X + 40, BOARD_Y + 21 }, "×ֵ¥ױֱה¡@¢׃¢Ü¢ג¢׃¢א¡@½T»{");
	Draw::displayString(posXY{ BOARD_X + 40, BOARD_Y + 22 }, "¢׃¢ב¢ׁ¡@¡@¡@¡@¡@¡@¡@¿ן³ז");


}

void setConsoleBoundSize(unsigned const int consoleX, unsigned const int consoleY)
{
	char command[100];
	std::ostringstream ostr;

	ostr << "mode con cols=" << consoleX << " lines=" << consoleY;
	std::string temp = ostr.str();
	for (unsigned int i = 0; i < temp.size() + 1; i++)
		command[i] = temp[i];
	system(command); //°ץ¦ז«ü¥O
}

void drawChess(posXY pos, int color) {
	canvas chess;
	string colorChess;
	if (color == WHITE)
		colorChess = "¡´";
	else if (color == BLACK)
		colorChess = "¡³";
	chess.boardContent = &colorChess;
	chess.drawBoard(pos, 1);
}

int main() {
	setConsoleBoundSize(96,35);
	while (1) {
		system("cls");
		Reversi reversi;
		reversi.initialBoard();
		drawChessBoard();
		Draw::drawAllChess(reversi);
		WordColor::setWordColor(WordColor::White, 1, WordColor::Violet, 1);
		Draw::drawChess(posXY{ 4,4 }, 1);
		Draw::drawChess(posXY{ 4,4 }, 1);
		canvas playerTermBoard;
		string player;
		WordColor::setWordColor(WordColor::White, 1, WordColor::Black, 1);
		player = "¶ֲ₪ט";
		playerTermBoard.boardContent = &player;
		playerTermBoard.drawBoard(posXY{ BOARD_X + 18,3 }, 1);
		WordColor::defaultColor();
		Draw::displayScore(reversi, reversi._ifPlay);
		while (reversi._ifPlay) {
			bool ifAvailible = 0;
			for (int i = 0; i < reversi._board.size(); i++) {
				for (int j = 0; j < reversi._board[i].size(); j++) {
					ifAvailible = ifAvailible | reversi.positionCheck(posXY{ j, i });
				}
			}
			if (!(ifAvailible)) {
				//Change player term
				reversi._handlePlayer = 3 - reversi._handlePlayer;
				canvas playerTermBoard;
				string player;
				if (reversi._handlePlayer == 1) {
					WordColor::setWordColor(WordColor::Black, 1, WordColor::White, 1);
					player = "¥ױ₪ט";
				}
				else {
					WordColor::setWordColor(WordColor::White, 1, WordColor::Black, 1);
					player = "¶ֲ₪ט";
				}
				playerTermBoard.boardContent = &player;
				playerTermBoard.drawBoard(posXY{ BOARD_X + 18,3 }, 1);
				WordColor::defaultColor();
			}
			//AI Control
			if (reversi.ifAIEnabled && reversi._handlePlayer == reversi.ifAIEnabled) {
				Sleep(AI_RESPONSE_TIME);
				struct bestPos
				{
					struct posXY pos;
					int ateChesses;
				};
				struct bestPos bestPosition { posXY{0,0}, 0 };
				for (int i = 0; i < reversi._board.size(); i++) {
					for (int j = 0; j < reversi._board[i].size(); j++) {
						if (reversi._ateChesses[i][j].size() > bestPosition.ateChesses) {
							bestPosition.ateChesses = reversi._ateChesses[i][j].size();
							bestPosition.pos = posXY{ j,i };
						}
					}
				}
				int cusorX = bestPosition.pos.posX;
				int cusorY = bestPosition.pos.posY;
				if (reversi._ateChesses[cusorY][cusorX].size() > 0) { //wheather the place is availible?
					reversi._board[cusorY][cusorX] = reversi._handlePlayer;
					for (int i = 0; i < reversi._ateChesses[cusorY][cusorX].size(); i++) {
						reversi._board[reversi._ateChesses[cusorY][cusorX][i].posY][reversi._ateChesses[cusorY][cusorX][i].posX] = reversi._handlePlayer;
						Draw::drawChess(posXY{ reversi._ateChesses[cusorY][cusorX][i].posX, reversi._ateChesses[cusorY][cusorX][i].posY }, reversi._handlePlayer);
						if (reversi._isAnimation)
							Sleep(300);
					}
					if (reversi._ifDeleteBoards) {
						reversi._boards.erase(reversi._boards.begin() + reversi.currentTerm + 1, reversi._boards.end());
						reversi._ifDeleteBoards = 0;
					}
					vector<vector<int> > boardNow = reversi._board;
					reversi._boards.push_back(boardNow);
					Draw::drawAllChess(reversi);
					bool tmpIfPlay = 1;
					Draw::displayScore(reversi, tmpIfPlay);

					//Record
					Draw::displayRecord(reversi, posXY{ cusorX, cusorY }, reversi._handlePlayer);

					//Change player term
					reversi._handlePlayer = 3 - reversi._handlePlayer;
					canvas playerTermBoard;
					string player;
					if (reversi._handlePlayer == 1) {
						WordColor::setWordColor(WordColor::Black, 1, WordColor::White, 1);
						player = "¥ױ₪ט";
					}
					else {
						WordColor::setWordColor(WordColor::White, 1, WordColor::Black, 1);
						player = "¶ֲ₪ט";
					}
					playerTermBoard.boardContent = &player;
					playerTermBoard.drawBoard(posXY{ BOARD_X + 18,3 }, 1);
					WordColor::defaultColor();
					reversi._hadlePlayerRecord.push_back(reversi._handlePlayer);
					reversi.currentTerm++;
				}
			} else
				Key::keyControl(Key::getKey(), reversi);
			//bool ifPlay = 1;
			//reversi.gameOver(1, ifPlay);//Test
		}
	}
	system("pause");
	return 0;
}

