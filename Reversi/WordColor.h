#pragma once
#include <Windows.h>

namespace WordColor
{
	enum Color
	{
		Black = 0,
		Bule = 1,
		Green = 2,
		Cyan = 3,
		Red = 4,
		Violet = 5,
		Yellow = 6,
		White = 7,
		Gray = 8
	};
}

namespace WordColor
{
	struct WordColorFormat
	{
		WordColorFormat(Color word, bool word_intensity, Color background, bool background_intensity)
			:wordColor(word), wordIntensity(word_intensity), backgroundColor(background), backgroundIntensity(background_intensity) {}
		Color wordColor;
		bool wordIntensity;
		Color backgroundColor;
		bool backgroundIntensity;
	};
	const WordColorFormat getNowFormat();
	//輸出文字邊框「┐」時word是White，word_intensity請用false，否則右邊界會神秘失蹤
	void setWordColor(WordColorFormat format);
	void setWordColor(Color word, bool word_intensity = true, Color background = Black, bool background_intensity = true);
	void defaultColor();
}