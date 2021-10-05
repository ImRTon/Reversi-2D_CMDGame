#pragma once
#include "Reversi.h"
#include <string>
#include <vector>

namespace WordColor { enum Color; };

namespace MColor {
	struct menuColor {
		WordColor::Color cusor;
		WordColor::Color cusorBackground;
		WordColor::Color menuButton;
		WordColor::Color menuButtonBackground;
		std::vector<bool> idensity; //cusor¡BcusorBackground¡BmenuButton¡BmenuButtonBackground
	};
	typedef struct menuColor MenuColor;
};

/*struct posXY
{
	int posX;
	int posY;
};*/

namespace Key
{
	int getKey(); //returns the specific key ascii code. Ignore the useless one.
	void keyControl(int keyAscii, Reversi & reversi);
	int menuControl(int keyAscii, std::vector<struct posXY> positions, std::vector<std::string> contents, int length, int cusorPos, MColor::MenuColor menuColors);

	extern struct posXY _playerCusor; //player's cusor position
}