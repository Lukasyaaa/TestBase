#pragma once
#include <iostream>
#include <iomanip>

void SetColor(int text, int background);
void gotoxy(int x, int y);

void equateString(char*& ourStr, const char* newStr, size_t countCopy = 0, size_t startCopy = 0);
const char* getSubstr(const char* str, size_t pos, size_t count);

bool isSymbolLetter(const char checkingChar);
bool isSymbolDigit(const char checkingChar);
bool isAllSymbolsLetters(const char* checkingString);
bool isAllSymbolsDigit(const char* checkingString);

int intFromString(const char* str);
const char* stringFromInt(int intNumber);

void reverseNumber(int& numb);
int getCountNumber(int number);
size_t getPosSymbol(const char* str, const char symb, size_t startPos = 0);

template<class T>
T* pushBackArray(T*& a, size_t& size, const T& value) {
	T* temp = new T[size + 1];
	for (size_t i = 0; i < size; i++) temp[i] = a[i];
	temp[size] = value;
	delete[] a;
	size++;
	a = temp;
	return temp;
}

template<class T>
T* pushBackArray(T*& a, size_t&& size, const T& value) {
	T* temp = new T[size + 1];
	for (size_t i = 0; i < size; i++) temp[i] = a[i];
	temp[size] = value;
	delete[] a;
	size++;
	a = temp;
	return temp;
}