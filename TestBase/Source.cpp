#include <iostream>
#include <iomanip>
#include <Windows.h>
#include "Functions.h"
#include "Menu.h"

#include "Main.h"

using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));

	system("mode con cols=100 lines=25");

	TestBase tb;
	tb.interact();
	system("cls");
}