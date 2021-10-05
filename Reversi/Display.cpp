#include "Display.h"
#include <iostream>
#include <Windows.h>
#include <wchar.h>
#include "Reversi.h"
#include "WordColor.h"
#include "KeyControl.h"
#include <thread>
#pragma comment(lib, "winmm.lib")
using std::cout;
using std::endl;

#define WHITE 1
#define BLACK 2
#define BLANK 0

void playMusic() {
	PlaySound("../music.wav", NULL, SND_FILENAME | SND_LOOP); //SND_FILENAME or SND_LOOP
}

void gotoxy(int x, int y, const int OFFSET_X, const int OFFSET_Y) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c;
	if (hOut == INVALID_HANDLE_VALUE)
	{
		std::cout << "handle failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	x = x + OFFSET_X;
	y = y + OFFSET_Y;

	if (x < 0 || y < 0)
		return;

	c.X = x; c.Y = y;
	SetConsoleCursorPosition(hOut, c);
}

canvas::canvas()
{
}

canvas::~canvas()
{
}

void canvas::drawBoard(struct posXY pos, int lengthRow) {
	for (int i = 0; i < lengthRow; i++) {
		gotoxy(0, 0, pos.posX, pos.posY+i);
		cout << boardContent[i] << endl;
	}
}

void Draw::drawChess(posXY chessPos, int charType)
{
	struct posXY pos = {4 + chessPos.posX * 4 + BOARD_X, 2 + chessPos.posY * 2 + BOARD_Y};
	gotoxy(0, 0, pos.posX, pos.posY);
	if (charType == WHITE)
		cout << "●";
	else if (charType == BLACK)
		cout << "○";
	else if (charType == BLANK)
		cout << "　";
	//else
		//cout << "～";
	//Sleep(300);
}

void Draw::drawAllChess(Reversi & reversi)
{
	for (int i = 0; i < reversi._board.size(); i++) {
		for (int j = 0; j < reversi._board[i].size(); j++) {
			Draw::drawChess(posXY{ j, i }, reversi._board[i][j]);
		}
	}
}

void Draw::displayScore(Reversi & reversi, bool & ifPlay)
{
	int playerBlack = 0, playerWhite = 0, blank = 0;
	for (int i = 0; i < reversi._board.size(); i++) {
		for (int j = 0; j < reversi._board[i].size(); j++) {
			if (reversi._board[i][j] == BLACK)
				playerBlack++;
			else if (reversi._board[i][j] == WHITE)
				playerWhite++;
			else
				blank++;
		}
	}

	WordColor::setWordColor(WordColor::Black, 1, WordColor::Bule, 0);
	int digit1 = playerBlack % 10;
	int digit2 = (playerBlack - digit1) / 10;
	gotoxy(BOARD_X, BOARD_Y, 6, 21);
	if (digit2)
		cout << digit2;
	gotoxy(BOARD_X, BOARD_Y, 7, 21);
	cout << digit1;

	WordColor::setWordColor(WordColor::White, 1, WordColor::Bule, 0);
	digit1 = playerWhite % 10;
	digit2 = (playerWhite - digit1) / 10;
	gotoxy(BOARD_X, BOARD_Y, 30, 21);
	if (digit2)
		cout << digit2;
	gotoxy(BOARD_X, BOARD_Y, 31, 21);
	cout << digit1;
	WordColor::defaultColor();
	if (blank == 0) {
		int winner = 0;
		if (playerBlack > playerWhite)
			winner = BLACK;
		else if (playerBlack < playerWhite)
			winner = WHITE;
		reversi.gameOver(winner, reversi._ifPlay);		
	}
}

void Draw::displayString(posXY pos, string content)
{
	gotoxy(0, 0, pos.posX, pos.posY);
	cout << content;
}

void Draw::drawMenu(Reversi & reversi)
{
	canvas Menu;
	WordColor::setWordColor(WordColor::Black, 1, WordColor::Gray, 1);
	string menuContents[] = {
		"　　　　　　　　",
		"　【ＭＥＮＵ】　",
		"　　　　　　　　",
		"　　　繼續　　　",
		"　　　　　　　　",
		"　　↖上一步　　",
		"　　　　　　　　",
		"　　↘下一步　　",
		"　　　　　　　　",
		"　　重新開始　　",
		"　　　　　　　　",
		"　　　音樂　　　",
		"　　　　　　　　",
		"　　　ＡＩ　　　",
		"　　　　　　　　",
		"　　　動畫　　　",
		"　　　　　　　　",
		"　　離開遊戲　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　"
	}; 
	Menu.boardContent = menuContents;
	Menu.drawBoard(posXY{ 0,2 }, 27);
	vector<struct posXY> positions;
	for (int i = 0; i < 8; i++) {
		positions.push_back(posXY{ 2,5 + i * 2 });
	}
	vector<string> buttonContents;
	buttonContents.push_back("　　繼續　　");
	buttonContents.push_back("　↖上一步　");
	buttonContents.push_back("　↘下一步　");
	buttonContents.push_back("　重新開始　");
	buttonContents.push_back("　　音樂　　");
	buttonContents.push_back("　　ＡＩ　　");
	buttonContents.push_back("　　動畫　　");
	buttonContents.push_back("　離開遊戲　");
	vector <bool> idensities = { 1,1, 1,1 };
	MColor::MenuColor menuColors = {
		WordColor::Red,	 //cusor
		WordColor::White,	 //cusorBackground
		WordColor::Gray,	 //menuButton
		WordColor::Black,	 //menuButtonBackground
		idensities
	}; 
	WordColor::setWordColor(WordColor::White, 1, WordColor::Red, 1);
	Draw::displayString(posXY{ 2,5 }, "　　繼續　　");
	WordColor::defaultColor();
	int menuRes = Key::menuControl(Key::getKey(), positions, buttonContents, 8, 0, menuColors);

	
	switch (menuRes)
	{
	case 0: //繼續
	{
		
	}
		break;
	case 1 : //上一步
		if (reversi.currentTerm - 1 >= 0) {
			reversi.currentTerm--;
			reversi._ifDeleteBoards = 1;
			reversi.loadBoard(reversi.currentTerm);
		}
		break;
	case 2 : //下一步
		if (reversi.currentTerm + 1 < reversi._boards.size()) {
			reversi.currentTerm++;
			reversi._ifDeleteBoards = 1;
			reversi.loadBoard(reversi.currentTerm);
		}
		break;
	case 3 : //重新開始
		reversi._ifPlay = 0;
		break;
	case 4 : //音樂
		if (reversi.isMusic == 0)
		{
			std::thread musicTread(playMusic);
			musicTread.detach();
			reversi.isMusic = 1;
		}
		break;
	case 5 : //AI
		if (!(reversi.ifAIEnabled)) {
			reversi.ifAIEnabled = 3 - reversi._handlePlayer;
			WordColor::setWordColor(WordColor::Black, 1, WordColor::Yellow, 0);
			Draw::displayString(posXY{BOARD_X + 29, BOARD_Y - 2}, " AI On ");
			WordColor::defaultColor();
			Draw::displayString(posXY{ BOARD_X + 36, BOARD_Y - 2 }, " ");
		}
		else {
			reversi.ifAIEnabled = 0;
			WordColor::setWordColor(WordColor::White, 1, WordColor::Gray, 0);
			Draw::displayString(posXY{ BOARD_X + 29, BOARD_Y - 2 }, " AI Off ");
			WordColor::defaultColor();
		}
		break; 
	case 6: //動畫
		reversi._isAnimation = !reversi._isAnimation;
		break;
	case 7: //離開
		exit(1);
			break;
	default:
		break;
	}
	canvas noMenu;
	WordColor::setWordColor(WordColor::White, 1, WordColor::Black, 1);
	string blankContents[] = {
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　",
		"　　　　　　　　"
	};
	noMenu.boardContent = blankContents;
	noMenu.drawBoard(posXY{ 0,2 }, 27);
}

void Draw::displayRecord(Reversi & reversi, posXY pos, int chessType)
{
	string ENGLetter[] = {
		"Ａ",
		"Ｂ",
		"Ｃ",
		"Ｄ",
		"Ｅ",
		"Ｆ",
		"Ｇ",
		"Ｈ"
	};
	string BigNumber[] = {
		"１",
		"２",
		"３",
		"４",
		"５",
		"６",
		"７",
		"８"
	};
	if (chessType == -1)
		reversi.chessRecords.clear();
	else {
		struct chessRecord aRecord { pos, chessType };
		reversi.chessRecords.push_back(aRecord);
	}
	WordColor::setWordColor(WordColor::Cyan, 1, WordColor::Gray, 0);
	displayString(posXY{ BOARD_X + 6 + 34, BOARD_Y }, "　　　　　　　　　");
	int j = 0;
	for (int k = (int)reversi.chessRecords.size() - 1; k >= (int)reversi.chessRecords.size() - 18; k--)
	{
		if (k < 0) {
			displayString(posXY{BOARD_X + 6 + 34, BOARD_Y + 1 + j}, "　　　　　　　　　");
		}
		else {
			displayString(posXY{ BOARD_X + 6 + 34, BOARD_Y + 1 + j }, "　");
			if (reversi.chessRecords[k].chessType == WHITE)
				displayString(posXY{ BOARD_X + 5 + 37, BOARD_Y + 1 + j }, "白棋");
			else if (reversi.chessRecords[k].chessType == BLACK)
				displayString(posXY{ BOARD_X + 5 + 37, BOARD_Y + 1 + j }, "黑棋");
			displayString(posXY{ BOARD_X + 5 + 41, BOARD_Y + 1 + j }, "落子於");
			displayString(posXY{ BOARD_X + 5 + 47, BOARD_Y + 1 + j }, ENGLetter[reversi.chessRecords[k].chessPos.posX] + BigNumber[reversi.chessRecords[k].chessPos.posY]);
			displayString(posXY{ BOARD_X + 5 + 51, BOARD_Y + 1 + j }, "　");
		}
		displayString(posXY{ BOARD_X + 6 + 34, BOARD_Y + 18 }, "　　　　　　　　　");
		j++;
	}
}
