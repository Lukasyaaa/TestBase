#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <Windows.h>

#include "Menu.h"
#include "Functions.h"

using namespace std;

int vertical_menu(char** menuItem, HORIZONTAL_POSITION hp, VERTICAL_POSITION vp, ALIGNMENT allignment, int textColor, int backColor) {
	HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(wHnd, &consoleInfo);
	int width = consoleInfo.dwSize.X;
	int height = consoleInfo.dwSize.Y;

	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(wHnd, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(wHnd, &structCursorInfo);

	int size = _msize(menuItem) / sizeof(char*);
	int maxLength = 0;
	for (size_t i = 0; i < size; i++) {
		if (strlen(menuItem[i]) > maxLength)
			maxLength = strlen(menuItem[i]);
	}

	int x, y;
	switch (hp) {
	case HORIZONTAL_POSITION::LEFT:     x = 1;                       break;
	case HORIZONTAL_POSITION::CENTER:   x = (width - maxLength) / 2; break;
	case HORIZONTAL_POSITION::RIGHT:    x = width - maxLength - 1;   break;
	}
	switch (vp) {
	case VERTICAL_POSITION::TOP:      y = 1;                   break;
	case VERTICAL_POSITION::CENTER:   y = (height - size) / 2; break;
	case VERTICAL_POSITION::BOTTOM:   y = height - size - 1;   break;
	}

	char** menuItemChanged = new char* [size];
	char space[] = "                              ";
	for (size_t i = 0; i < size; i++) {
		menuItemChanged[i] = new char[maxLength + 1];
		menuItemChanged[i][0] = '\0';
		switch (allignment) {
		case ALIGNMENT::LEFT:
			strcat(menuItemChanged[i], menuItem[i]);
			strncat(menuItemChanged[i], space, maxLength - strlen(menuItem[i]));
			break;
		case ALIGNMENT::CENTER:
			strncat(menuItemChanged[i], space, (maxLength - strlen(menuItem[i])) / 2);
			strcat(menuItemChanged[i], menuItem[i]);
			strncat(menuItemChanged[i], space, maxLength - strlen(menuItem[i]) - (maxLength - strlen(menuItem[i])) / 2);
			break;
		case ALIGNMENT::RIGHT:
			strncat(menuItemChanged[i], space, maxLength - strlen(menuItem[i]));
			strcat(menuItemChanged[i], menuItem[i]);
			break;
		}
	}

	int position = 0;
	char choise;
	do {
		// print
		for (size_t i = 0; i < size; i++) {
			if (i == position)
				SetColor(backColor, textColor);
			else SetColor(textColor, backColor);
			gotoxy(x, y + i);
			cout << setw(maxLength) << menuItemChanged[i];
		}

		//click
		choise = _getch();
		switch (choise) {
		case UP_ARROW:
			if (position > 0) position--;
			else position = size - 1;
			break;
		case DOWN_ARROW:
			if (position < size - 1) position++;
			else position = 0;
			break;
		case ESC:
			return -1;

		default: break;
		}
	} while (choise != ENTER);

	for (size_t i = 0; i < 2; i++) {
		SetColor(textColor, backColor);
		gotoxy(x, y + position);
		cout << setw(maxLength) << menuItemChanged[position];
		Sleep(200);

		SetColor(backColor, textColor);
		gotoxy(x, y + position);
		cout << setw(maxLength) << menuItemChanged[position];
		Sleep(200);
	}
	SetColor(textColor, backColor);
	structCursorInfo.bVisible = TRUE;
	SetConsoleCursorInfo(wHnd, &structCursorInfo);

	///// Alt CLS
	char* voidItem = new char[maxLength + 1];
	for (size_t i = 0; i < maxLength; i++) voidItem[i] = ' ';
	voidItem[maxLength] = '\0';
	for (size_t i = 0; i < size; i++) {
		gotoxy(x, y + i);
		cout << voidItem;
	}
	return position;
}

int vertical_menu(char** menuItem, int xPos, int yPos, ALIGNMENT allignment, int textColor, int backColor) {
	HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(wHnd, &consoleInfo);
	int width = consoleInfo.dwSize.X;
	int height = consoleInfo.dwSize.Y;

	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(wHnd, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(wHnd, &structCursorInfo);

	int size = _msize(menuItem) / sizeof(char*);
	int maxLength = 0;
	for (size_t i = 0; i < size; i++) {
		if (strlen(menuItem[i]) > maxLength)
			maxLength = strlen(menuItem[i]);
	}

	char** menuItemChanged = new char* [size];
	char space[] = "                              ";
	for (size_t i = 0; i < size; i++) {
		menuItemChanged[i] = new char[maxLength];
		menuItemChanged[i][0] = '\0';
		switch (allignment) {
		case ALIGNMENT::LEFT:
			strcat(menuItemChanged[i], menuItem[i]);
			strncat(menuItemChanged[i], space, maxLength - strlen(menuItem[i]));
			break;
		case ALIGNMENT::CENTER:
			strncat(menuItemChanged[i], space, (maxLength - strlen(menuItem[i])) / 2);
			strcat(menuItemChanged[i], menuItem[i]);
			strncat(menuItemChanged[i], space, maxLength - strlen(menuItem[i]) - (maxLength - strlen(menuItem[i])) / 2);
			break;
		case ALIGNMENT::RIGHT:
			strncat(menuItemChanged[i], space, maxLength - strlen(menuItem[i]));
			strcat(menuItemChanged[i], menuItem[i]);
			break;
		}
	}

	int position = 0;
	int x = xPos, y = yPos;
	char choise;
	do {
		// print
		for (size_t i = 0; i < size; i++) {
			if (i == position)
				SetColor(backColor, textColor);
			else SetColor(textColor, backColor);
			gotoxy(x, y + i);
			cout << setw(maxLength) << menuItemChanged[i];
		}

		//click
		choise = _getch();
		switch (choise) {
		case UP_ARROW:
			if (position > 0) position--;
			else position = size - 1;
			break;
		case DOWN_ARROW:
			if (position < size - 1) position++;
			else position = 0;
			break;
		case ESC:
			return -1;
		default: break;
		}
	} while (choise != ENTER);

	for (size_t i = 0; i < 2; i++) {
		SetColor(textColor, backColor);
		gotoxy(x, y + position);
		cout << setw(maxLength) << menuItemChanged[position];
		Sleep(200);

		SetColor(backColor, textColor);
		gotoxy(x, y + position);
		cout << setw(maxLength) << menuItemChanged[position];
		Sleep(200);
	}
	SetColor(textColor, backColor);
	structCursorInfo.bVisible = TRUE;
	SetConsoleCursorInfo(wHnd, &structCursorInfo);

	///// Alt CLS
	char* voidItem = new char[maxLength + 1];
	for (size_t i = 0; i < maxLength; i++) voidItem[i] = ' ';
	voidItem[maxLength] = '\0';
	for (size_t i = 0; i < size; i++) {
		gotoxy(x, y + i);
		cout << voidItem;
	}
	return position;
}