#include "Functions.h"
#include <Windows.h>

using namespace std;

void SetColor(int text, int background) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)((background << 4) | text));
}
void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void equateString(char*& ourStr, const char* newStr, size_t countCopy, size_t startCopy) {
	if (countCopy == 0) countCopy = strlen(newStr);
	ourStr = new char[countCopy + 1];
	for (size_t i = startCopy, j = 0; i < countCopy + startCopy; i++) ourStr[j++] = newStr[i];
	ourStr[countCopy] = '\0';
}
const char* getSubstr(const char* str, size_t pos, size_t count) {
	char* substr = new char[count + 1];
	for (size_t i = pos; i < pos + count; i++) substr[i - pos] = str[i];
	substr[count] = '\0';
	return substr;
}

bool isSymbolLetter(const char checkingChar) {
	return (checkingChar >= 65 && checkingChar <= 90) || (checkingChar >= 97 && checkingChar <= 122);
}
bool isSymbolDigit(const char checkingChar) {
	return (checkingChar >= 48 && checkingChar <= 57);
}
bool isAllSymbolsLetters(const char* checkingString) {
	for (size_t i = 0; i < strlen(checkingString); i++)
		if (!isSymbolLetter(checkingString[i])) return 0;
	return 1;
}
bool isAllSymbolsDigit(const char* checkingString) {
	bool haveOneDot = false;
	for (size_t i = 0; i < strlen(checkingString); i++) {
		if (!isdigit(checkingString[i]) && ((checkingString[i] == '-') ? i != 0 : 1) && ((checkingString[i] == '.') ? !haveOneDot : 1)) return 0;
		if (checkingString[i] == '.') haveOneDot = true;
	}
	return 1;
}

int intFromString(const char* str) {
	int number = 0;
	if (isAllSymbolsDigit(str)) {
		size_t index = 0;
		if (str[0] == '-') index++;
		for (; index < strlen(str); index++) {
			number += (str[index] - 48) * pow(10, strlen(str) - index - 1);
		}
		if (str[0] == '-') number *= -1;
	}
	return number;
}
const char* stringFromInt(int intNumber) {
	char* str = new char[getCountNumber(intNumber) + 1];
	size_t index = 0;
	if (intNumber != abs(intNumber)) {
		str[0] = '-';
		index++;
		intNumber *= -1;
	}
	for (; index < ((str[0] == '-') ? getCountNumber(intNumber) + 1 : getCountNumber(intNumber)); index++) {
		str[((str[0] == '-') ? getCountNumber(intNumber) + 2 : getCountNumber(intNumber)) - index - 1] = int(intNumber / pow(10, ((str[0] == '-') ? index - 1 : index))) % 10 + 48;
	}
	str[index] = '\0';
	return str;
}

void reverseNumber(int& numb) {
	if (numb != 0) {
		int reversedNumber = 0;
		for (size_t i = 0; i < getCountNumber(numb); i++) {
			reversedNumber += int(numb / pow(10, i)) % 10 * pow(10, getCountNumber(numb) - i - 1);
		}
		numb = reversedNumber;
	}
}
int getCountNumber(int number) {
	int count = 0;
	if (number <= 0) {
		count++;
		number = -number;
	}
	while (number) {
		count++;
		number /= 10;
	}
	return count;
}
size_t getPosSymbol(const char* str, const char symb, size_t startPos) {
	for (size_t i = startPos; str[i] != '\0'; i++) {
		if (symb == str[i]) return i;
	}
	return strlen(str);
}