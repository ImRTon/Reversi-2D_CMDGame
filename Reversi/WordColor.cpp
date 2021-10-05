#include "WordColor.h"
#include <iostream>

namespace
{
	WordColor::WordColorFormat nowFormat = { WordColor::White, true, WordColor::Black, true };
	//²{¦b¤å¦r®æ¦¡
}

const WordColor::WordColorFormat WordColor::getNowFormat()
{
	return nowFormat;
}

void WordColor::setWordColor(WordColorFormat format)
{
	WordColor::setWordColor(format.wordColor, format.wordIntensity, format.backgroundColor, format.backgroundIntensity);
}

void WordColor::setWordColor(Color word, bool word_intensity, Color background, bool background_intensity)
{
	//­I´º»P¤å¦rÃC¦â¬°
   // 1~15¬° ¶Â ·tÂÅ ·tºñ ·t«C ·t¬õ ·tµµ ·t¶À ·t¥Õ ¦Ç
   //         0   1     2   3    4    5    6    7   8
   //           «GÂÅ «Gºñ «G«C «G¬õ «Gµµ «G¶À  «G¥Õ
   //            9    10   11   12    13   14    15
	static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);

	if (hConsole == INVALID_HANDLE_VALUE)
	{
		std::cout << "handle failed" << std::endl;
		//_getch();
		exit(EXIT_FAILURE);
	}

	static const char INTENSITY = 8;

	unsigned char total = word;
	if (word_intensity == true)
		if (total != Gray && total != Black) //¶Â¡B¦Ç¦â¨S¦³«G¦â
			total += INTENSITY;

	if (background_intensity == true)
	{
		if (background != Black && background != Gray)
			total += (background + INTENSITY) * 16;
		else
			total += background * 16;
	}
	else
		total += background * 16;

	SetConsoleTextAttribute(hConsole, total);
	nowFormat = WordColorFormat(word, word_intensity, background, background_intensity);
}

void WordColor::defaultColor() //back to default color
{
	WordColor::setWordColor(WordColor::White, true, WordColor::Black, true);
}