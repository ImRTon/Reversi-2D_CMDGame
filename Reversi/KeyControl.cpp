#include "KeyControl.h"
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include "WordColor.h"
#include "Display.h"

#define KEY_LEFT 1
#define KEY_UP 2
#define KEY_RIGHT 3
#define KEY_DOWN 4
#define KEY_ENTER 5
#define KEY_ESC 6
#define WHITE 1
#define BLACK 2
#define BLANK 0

struct posXY Key::_playerCusor; //player's cusor position





int Key::getKey()
{
	int ascii = _getch();
	std::cin.clear();

	switch (ascii)
	{
	case 75 : //¡ö Left
	case 65 :
	case 97 : 
		return KEY_LEFT;
		break;
	case 72 : //¡ô Up
	case 87 :
	case 119 :
		return KEY_UP;
		break;
	case 77 : //¡÷ Right
	case 68 :
	case 100 :
		return KEY_RIGHT;
		break;
	case 80 : //¡õ Down
	case 83 :
	case 115 :
		return KEY_DOWN;
		break;
	case 13: //Enter
	case 32 : //Space
		return KEY_ENTER;
		break;
	case 27: //Esc
		return KEY_ESC;
		break;
	default:
		return getKey();
		break;
	}
}

void drawCusor(struct posXY pos, Reversi & reversi) {
	Draw::drawChess(pos, reversi._board[pos.posY][pos.posX]);
	/*canvas chess;
	string colorChess;
	int boardObject = reversi._board[pos.posY][pos.posX];
	if (boardObject == WHITE)
		colorChess = "¡´";
	else if (boardObject == BLACK)
		colorChess = "¡³";
	else if (boardObject == BLANK)
		colorChess = " ";
	chess.boardContent = &colorChess;
	chess.drawBoard(posXY{ pos.posX, pos.posY }, 1);*/
}

void Key::keyControl(int keyAscii, Reversi & reversi)
{
	switch (keyAscii)
	{
	case KEY_LEFT:
		if (_playerCusor.posX - 1 >= 0) {
			drawCusor(posXY{ _playerCusor.posX, _playerCusor.posY }, reversi);
			WordColor::setWordColor(WordColor::White, 1, WordColor::Violet, 1);
			drawCusor(posXY{ _playerCusor.posX - 1, _playerCusor.posY }, reversi);
			_playerCusor.posX--;
		}
		break;
	case KEY_UP:
		if (_playerCusor.posY - 1 >= 0) {
			drawCusor(posXY{ _playerCusor.posX, _playerCusor.posY }, reversi);
			WordColor::setWordColor(WordColor::White, 1, WordColor::Violet, 1);
			drawCusor(posXY{ _playerCusor.posX, _playerCusor.posY - 1 }, reversi);
			_playerCusor.posY--;
		}
		break;
	case KEY_RIGHT:
		if (_playerCusor.posX + 1 < 8) {
			drawCusor(posXY{ _playerCusor.posX, _playerCusor.posY }, reversi);
			WordColor::setWordColor(WordColor::White, 1, WordColor::Violet, 1);
			drawCusor(posXY{ _playerCusor.posX + 1, _playerCusor.posY }, reversi);
			_playerCusor.posX++;
		}
		break;
	case KEY_DOWN:
		if (_playerCusor.posY + 1 < 8) {
			drawCusor(posXY{ _playerCusor.posX, _playerCusor.posY }, reversi);
			WordColor::setWordColor(WordColor::White, 1, WordColor::Violet, 1);
			drawCusor(posXY{ _playerCusor.posX, _playerCusor.posY + 1 }, reversi);
			_playerCusor.posY++;
		}
		break;
	case KEY_ENTER:
		{
			int cusorX = _playerCusor.posX;
			int cusorY = _playerCusor.posY;
			if (reversi._ateChesses[cusorY][cusorX].size() > 0) { //wheather the place is availible?
				reversi._board[cusorY][cusorX] = reversi._handlePlayer;
				for (int i = 0; i < reversi._ateChesses[cusorY][cusorX].size(); i++) {
					reversi._board[reversi._ateChesses[cusorY][cusorX][i].posY][reversi._ateChesses[cusorY][cusorX][i].posX] = reversi._handlePlayer;
					Draw::drawChess(posXY { reversi._ateChesses[cusorY][cusorX][i].posX, reversi._ateChesses[cusorY][cusorX][i].posY}, reversi._handlePlayer);
					if (reversi._isAnimation)
						Sleep(300);
				}
				if (reversi._ifDeleteBoards) {
					reversi._boards.erase(reversi._boards.begin() + reversi.currentTerm + 1, reversi._boards.end());
					reversi._hadlePlayerRecord.erase(reversi._hadlePlayerRecord.begin() + reversi.currentTerm + 1, reversi._hadlePlayerRecord.end());
					reversi._ifDeleteBoards = 0;
				}
				vector<vector<int> > boardNow = reversi._board;
				reversi._boards.push_back(boardNow);
				//Draw::drawAllChess(reversi);
				bool tmpIfPlay = 1;
				Draw::displayScore(reversi, tmpIfPlay);

				//Record
				Draw::displayRecord(reversi, posXY{cusorX, cusorY}, reversi._handlePlayer);

				//Change player term
				reversi._handlePlayer = 3 - reversi._handlePlayer;
				canvas playerTermBoard;
				string player;
				if (reversi._handlePlayer == 1) {
					WordColor::setWordColor(WordColor::Black, 1, WordColor::White, 1);
					player = "¥Õ¤è";
				}
				else {
					WordColor::setWordColor(WordColor::White, 1, WordColor::Black, 1);
					player = "¶Â¤è";
				}
				playerTermBoard.boardContent = &player;
				playerTermBoard.drawBoard(posXY{ BOARD_X + 18,3 }, 1);
				WordColor::defaultColor();
				reversi._hadlePlayerRecord.push_back(reversi._handlePlayer);
				reversi.currentTerm++;
			}
		}
		break;
	case KEY_ESC :
		Draw::drawMenu(reversi);
		break;
	default:
		break;
	}
	WordColor::defaultColor();
}

int Key::menuControl(int keyAscii, std::vector<struct posXY> positions, std::vector<std::string> contents, int length, int cusorPos, MColor::MenuColor menuColors)
{
	switch (keyAscii)
	{
	case KEY_LEFT:
	case KEY_UP:
		if (cusorPos - 1 >= 0) {
			//draw previous button
			WordColor::setWordColor(menuColors.menuButtonBackground, menuColors.idensity[3], menuColors.menuButton, menuColors.idensity[2]);
			Draw::displayString(positions[cusorPos], contents[cusorPos]);
			//draw current button
			WordColor::setWordColor(menuColors.cusorBackground, menuColors.idensity[1], menuColors.cusor, menuColors.idensity[0]);
			Draw::displayString(positions[cusorPos - 1], contents[cusorPos - 1]);
			cusorPos--;
		}
		break;
	case KEY_RIGHT:
	case KEY_DOWN:
		if (cusorPos + 1 < positions.size()) {
			//draw previous button
			WordColor::setWordColor(menuColors.menuButtonBackground, menuColors.idensity[3], menuColors.menuButton, menuColors.idensity[2]);
			Draw::displayString(positions[cusorPos], contents[cusorPos]);
			//draw current button
			WordColor::setWordColor(menuColors.cusorBackground, menuColors.idensity[1], menuColors.cusor, menuColors.idensity[0]);
			Draw::displayString(positions[cusorPos + 1], contents[cusorPos + 1]);
			cusorPos++;
		}
		break;
	case KEY_ENTER:
		//draw previous button
		WordColor::setWordColor(menuColors.menuButtonBackground, menuColors.idensity[3], menuColors.menuButton, menuColors.idensity[2]);
		Draw::displayString(positions[cusorPos], contents[cusorPos]);
		WordColor::defaultColor();
		return cusorPos;
	break;
	default:
		break;
	}
	return Key::menuControl(Key::getKey(), positions, contents, length, cusorPos, menuColors);
	WordColor::defaultColor();
}

