#include "WordColor.h"
#include <iostream>

namespace
{
	WordColor::WordColorFormat nowFormat = { WordColor::White, true, WordColor::Black, true };
	//�{�b��r�榡
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
	//�I���P��r�C�⬰
   // 1~15�� �� �t�� �t�� �t�C �t�� �t�� �t�� �t�� ��
   //         0   1     2   3    4    5    6    7   8
   //           �G�� �G�� �G�C �G�� �G�� �G��  �G��
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
		if (total != Gray && total != Black) //�¡B�Ǧ�S���G��
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