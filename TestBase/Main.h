#pragma once
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <conio.h>
#include "Functions.h"
#include "Menu.h"
#include "InfoHelpful.h"

#define countCols 100

#define UserParam_1 "Логин"
#define UserParam_2 "Пароль"
#define UserParam_3 "ФИО"
#define UserParam_4 "Телефон"
#define UserParam_5 "IP"

using namespace std;

const char* replaceSpaceOnLines(const char* text) {
	bool haveSpace = false;
	for (size_t i = 0; text[i] != '\0'; i++) {
		if (isspace(text[i])) haveSpace = true;
	}
	if (haveSpace) {
		char* newText = new char[strlen(text) + 1];
		for (size_t i = 0; text[i] != '\0'; i++) {
			if (isspace(text[i])) newText[i] = '_';
			else newText[i] = text[i];
		}
		newText[strlen(text)] = '\0';
		return newText;
	}
	return text;
}

class Exercise {
	char* question = nullptr;
	char** variants = new char* [4];
	size_t correctAnswer = 3;
public:
	Exercise(const char* question = nullptr);
	Exercise(const Exercise& obj);
	~Exercise();

	void setQuestion(const char* newQuestion);
	void setFirstVariant(const char* newVariant);
	void setSecondVariant(const char* newVariant);
	void setThirdVariant(const char* newVariant);
	void setFourthVariant(const char* newVariant);

	Exercise& operator=(const Exercise& obj);

	const char* getQuestion() const;
	char** getVariants() const {
		return this->variants;
	}
};

Exercise::Exercise(const char* question) {
	if (question && isAllSymbolsLetters(question)) equateString(this->question, question);
}
Exercise::Exercise(const Exercise& obj) {
	equateString(this->question, obj.question);
	for (size_t i = 0; i < 4; i++) equateString(this->variants[i], obj.variants[i]);
}
Exercise::~Exercise() {
	delete this->question;
	for (size_t i = 0; i < 4; i++) delete this->variants[i];
	delete[] this->variants;
}

void Exercise::setQuestion(const char* newQuestion) {
	equateString(this->question, newQuestion);
}
void Exercise::setFirstVariant(const char* newVariant) {
	equateString(this->variants[0], newVariant);
}
void Exercise::setSecondVariant(const char* newVariant) {
	equateString(this->variants[1], newVariant);
}
void Exercise::setThirdVariant(const char* newVariant) {
	equateString(this->variants[2], newVariant);
}
void Exercise::setFourthVariant(const char* newVariant) {
	equateString(this->variants[3], newVariant);
}

Exercise& Exercise::operator=(const Exercise& obj) {
	if (this != &obj) {
		equateString(this->question, obj.question);
		for (size_t i = 0; i < 4; i++) equateString(this->variants[i], obj.variants[i]);
	}
	return *this;
}

const char* Exercise::getQuestion() const {
	return this->question;
}

class Test {
	std::vector<Exercise> exercises;
	size_t correctAnswers = 0;
	size_t numbStopped = 0;
	bool isCompleted = false;
	char** category = new char* [2];
public:
	Test();
	Test(const Test& obj);
	~Test();

	const std::vector<Exercise> getExercises() const;
	char** getCategory() const;
	size_t getCorrectAnswers() const;
	size_t getNumbStopped() const;
	bool getIsCompleted() const;

	void setSubject(const char* newStr);
	void setNumbStopped(const size_t newNumbStopped);
	void setTheme(const char* newStr);
	void setCorrectAnswers(const int correctAnswers);

	void makeCompleted();
	void retakeTest();
	void incrementCorrectAnswers();
	void addExercise(const Exercise& ex);

	Test& operator=(const Test& obj);
};

Test::Test() {}
Test::Test(const Test& obj) {
	this->correctAnswers = obj.correctAnswers;
	this->numbStopped = obj.numbStopped;
	this->isCompleted = obj.isCompleted;
	for (size_t i = 0; i < 2; i++) equateString(this->category[i], obj.category[i]);
	this->exercises.resize(obj.exercises.size());
	for (size_t i = 0; i < obj.exercises.size(); i++) this->exercises[i] = obj.exercises[i];
}
Test::~Test() {
	for (size_t i = 0; i < 2; i++) delete this->category[i];
	delete[] this->category;
	this->exercises.clear();
}

const std::vector<Exercise> Test::getExercises() const {
	return this->exercises;
}
char** Test::getCategory() const {
	return this->category;
}
size_t Test::getCorrectAnswers() const {
	return this->correctAnswers;
}
size_t Test::getNumbStopped() const {
	return this->numbStopped;
}
bool Test::getIsCompleted() const {
	return this->isCompleted;
}

void Test::setSubject(const char* newStr) {
	equateString(this->category[0], newStr);
}
void Test::setNumbStopped(const size_t newNumbStopped) {
	this->numbStopped = newNumbStopped;
}
void Test::setTheme(const char* newStr) {
	equateString(this->category[1], newStr);
}
void Test::setCorrectAnswers(const int correctAnswers) {
	this->correctAnswers = correctAnswers;
}

void Test::makeCompleted() {
	this->isCompleted = true;
}
void Test::retakeTest() {
	this->isCompleted = false;
	this->correctAnswers = 0;
}
void Test::incrementCorrectAnswers() {
	if (this->correctAnswers < this->exercises.size()) ++correctAnswers;
}
void Test::addExercise(const Exercise& ex) {
	this->exercises.push_back(ex);
}

Test& Test::operator=(const Test& obj) {
	if (this != &obj) {
		this->correctAnswers = obj.correctAnswers;
		this->isCompleted = obj.isCompleted;
		this->numbStopped = obj.numbStopped;

		equateString(this->category[0], obj.category[0]);
		equateString(this->category[1], obj.category[1]);

		this->exercises.resize(obj.exercises.size());
		for (size_t i = 0; i < obj.exercises.size(); i++) this->exercises[i] = obj.exercises[i];
	}
	return *this;
}

class User {
	char* login = nullptr;
	char* password = nullptr;
	std::vector<Test> tests;

	char** fullName = new char* [3];
	char** ip = new char* [4];
	char* tel = nullptr;

	char** makeMenuOfTests(bool all = true) const;

	const void saveTestsResult() const;

	void signIn();

	void passTest();
	void checkResult();
public:
	User();
	User(const User& obj);
	~User();

	void setLogin(const char* text);
	void setPassword(const char* text);

	void setName(const char* text);
	void setSurname(const char* text);
	void setPatronymic(const char* text);

	void setFirstPartIp(const char* text);
	void setSecondPartIp(const char* text);
	void setThirdPartIp(const char* text);
	void setFourthPartIp(const char* text);

	void setTel(const char* text);

	const char* getLogin() const;
	const char* getPassword() const;
	const std::vector<Test> getTests() const;
	char** getFullName() const;
	char** getIp() const;
	const char* getTel() const;

	void reg(bool save = true);

	void saveUser();

	void loadTests();
	void loadTestResult();

	void interact();
};

char** User::makeMenuOfTests(bool all) const {
	size_t size = 0;
	for (size_t i = 0; i < this->tests.size() && !all; i++) {
		if (this->tests[i].getIsCompleted()) size++;
	}
	char** massiveTests = new char* [((all) ? this->tests.size() + 1 : size + 1)];
	for (size_t i = 0, k = 0; i < this->tests.size(); i++) {
		if (all || (!all && this->tests[i].getIsCompleted())) {
			massiveTests[k] = new char[strlen(this->tests[i].getCategory()[0]) + strlen(this->tests[i].getCategory()[1]) + ((this->tests[i].getIsCompleted() && all) ? 14 : 5)];
			massiveTests[k][0] = ' ';
			for (size_t j = 0; j < strlen(this->tests[i].getCategory()[0]); j++) massiveTests[k][j + 1] = this->tests[i].getCategory()[0][j];
			massiveTests[k][strlen(this->tests[i].getCategory()[0]) + 1] = ' ';
			for (size_t j = 0; j < strlen(this->tests[i].getCategory()[0]); j++) massiveTests[k][j + strlen(this->tests[i].getCategory()[0]) + 2] = this->tests[i].getCategory()[1][j];
			if (this->tests[i].getIsCompleted() && all) {
				massiveTests[k][strlen(this->tests[i].getCategory()[0]) + strlen(this->tests[i].getCategory()[1]) + 2] = '(';
				massiveTests[k][strlen(this->tests[i].getCategory()[0]) + strlen(this->tests[i].getCategory()[1]) + 3] = 'П';
				massiveTests[k][strlen(this->tests[i].getCategory()[0]) + strlen(this->tests[i].getCategory()[1]) + 4] = 'р';
				massiveTests[k][strlen(this->tests[i].getCategory()[0]) + strlen(this->tests[i].getCategory()[1]) + 5] = 'о';
				massiveTests[k][strlen(this->tests[i].getCategory()[0]) + strlen(this->tests[i].getCategory()[1]) + 6] = 'й';
				massiveTests[k][strlen(this->tests[i].getCategory()[0]) + strlen(this->tests[i].getCategory()[1]) + 7] = 'д';
				massiveTests[k][strlen(this->tests[i].getCategory()[0]) + strlen(this->tests[i].getCategory()[1]) + 8] = 'е';
				massiveTests[k][strlen(this->tests[i].getCategory()[0]) + strlen(this->tests[i].getCategory()[1]) + 9] = 'н';
				massiveTests[k][strlen(this->tests[i].getCategory()[0]) + strlen(this->tests[i].getCategory()[1]) + 10] = ')';
			}
			massiveTests[k][strlen(this->tests[i].getCategory()[0]) + strlen(this->tests[i].getCategory()[1]) + ((this->tests[i].getIsCompleted() && all) ? 11 : 2)] = ' ';
			massiveTests[k++][strlen(this->tests[i].getCategory()[0]) + strlen(this->tests[i].getCategory()[1]) + ((this->tests[i].getIsCompleted() && all) ? 12 : 3)] = '\0';
		}
	}
	massiveTests[((all) ? this->tests.size() : size)] = new char[] {" Выйти "};
	return massiveTests;
}

const void User::saveTestsResult() const {
	std::ofstream out("testResult.txt");
	for (size_t i = 0; i < this->tests.size(); i++) {
		if (this->tests[i].getIsCompleted() || this->tests[i].getNumbStopped()) {
			out << this->login << " " << this->tests[i].getCategory()[0] << " " << this->tests[i].getCategory()[1] << " " << this->tests[i].getCorrectAnswers() << " " << this->tests[i].getIsCompleted() << ((this->tests[i].getIsCompleted()) ? "" : " ") << ((this->tests[i].getIsCompleted()) ? "" : stringFromInt(this->tests[i].getNumbStopped())) << std::endl;
		}
	}
	out.close();
}

void User::signIn() {
	for (size_t i = 0; true; i++) {
		std::fstream in("users.txt");
		char buff[80];
		char insertedPassword[80];
		char insertedLogin[80];
		if (i != 0) {
			system("cls");
		}
		gotoxy(0, 0);
		std::cout << "Вход в Систему:\n----Введите Логин: ";
		std::cin >> insertedLogin;
		for (size_t j = 0; in >> buff;) {
			if (j % 7 == 0) {
				if (!strcmp(insertedLogin, buff)) break;
				j++;
			}
			else j++;
		}
		if (!strcmp(insertedLogin, buff)) {
			gotoxy(0, 2);
			std::cout << "----" << "Введите Пароль: ";
			std::cin >> insertedPassword;
			for (size_t j = 0; in >> buff;) {
				if (j % 7 == 0) {
					if (strcmp(insertedPassword, buff) == 0) break;
					j++;
				}
				else j++;
			}
		}
		if (!strcmp(insertedPassword, buff)) {
			equateString(this->login, insertedLogin);
			equateString(this->password, buff);
			in >> buff;
			equateString(this->fullName[0], buff);
			in >> buff;
			equateString(this->fullName[1], buff);
			in >> buff;
			equateString(this->fullName[2], buff);
			in >> buff;
			equateString(this->tel, buff);
			in >> buff;
			{
				char* ipStr = nullptr;
				equateString(ipStr, buff);
				equateString(this->ip[0], ipStr, getPosSymbol(ipStr, '.'));
				equateString(this->ip[1], ipStr + getPosSymbol(ipStr, '.') + 1, getPosSymbol(ipStr + getPosSymbol(ipStr, '.') + 1, '.'));
				equateString(this->ip[2], ipStr + getPosSymbol(ipStr + getPosSymbol(ipStr, '.') + 1, '.') + getPosSymbol(ipStr, '.') + 2, getPosSymbol(ipStr + getPosSymbol(ipStr + getPosSymbol(ipStr, '.') + 1, '.') + getPosSymbol(ipStr, '.') + 2, '.'));
				equateString(this->ip[3], ipStr + getPosSymbol(ipStr + getPosSymbol(ipStr + getPosSymbol(ipStr, '.') + 1, '.') + getPosSymbol(ipStr, '.') + 2, '.') + getPosSymbol(ipStr + getPosSymbol(ipStr, '.') + 1, '.') + getPosSymbol(ipStr, '.') + 3, getPosSymbol(ipStr + getPosSymbol(ipStr + getPosSymbol(ipStr + getPosSymbol(ipStr, '.') + 1, '.') + getPosSymbol(ipStr, '.') + 2, '.') + getPosSymbol(ipStr + getPosSymbol(ipStr, '.') + 1, '.') + getPosSymbol(ipStr, '.') + 3, '.'));
			}
			break;
			in.close();
		}
	}
	{
		std::fstream in("users.txt");
		char buff[80];
		if (tests.size() == 0 && in >> buff) {
			this->loadTests();
			this->loadTestResult();
		}
	}
	system("pause");
	system("cls");
}

void User::passTest() {
	if (tests.size() > 0) {
		size_t choose;
		choose = vertical_menu(this->makeMenuOfTests(), HORIZONTAL_POSITION::CENTER, VERTICAL_POSITION::CENTER, ALIGNMENT::CENTER);
		if (choose != -1 && choose != tests.size()) {
			if (this->tests[choose].getIsCompleted()) this->tests[choose].retakeTest();
			for (size_t i = this->tests[choose].getNumbStopped(); i < this->tests[choose].getExercises().size(); i++) {
				if (this->tests[choose].getNumbStopped()) this->tests[choose].setNumbStopped(0);
				int pressedButton = 0;
				int alreadyUsed[4];
				size_t posFocus = 0;
				for (size_t j = 0; pressedButton != 13 && pressedButton != 27; j++) {
					pressedButton = 0;
					gotoxy(0, 0);
					std::cout << i + 1 << ")" << this->tests[choose].getExercises()[i].getQuestion() << std::endl;
					if (j == 0) {
						for (size_t k = 0; k < 4; k++) alreadyUsed[k] = -1;
					}
					for (size_t k = 0; k < 4; k++) {
						if (j == 0) {
							size_t randNumber;
							bool isCan;
							do {
								isCan = true;
								randNumber = rand() % 4;
								for (size_t p = 0; p < 4; p++) {
									if (randNumber == alreadyUsed[p]) {
										isCan = false;
										break;
									}
								}
							} while (!isCan);
							if (k == posFocus) SetColor(0, 15);
							std::cout << " " << this->tests[choose].getExercises()[i].getVariants()[randNumber] << " ";
							alreadyUsed[k] = randNumber;
							SetColor(15, 0);
						}
						else {
							if (k == posFocus) SetColor(0, 15);
							std::cout << " " << this->tests[choose].getExercises()[i].getVariants()[alreadyUsed[k]] << " ";
							SetColor(15, 0);
						}
					}
					std::cout << std::endl << "Нажмите A для перемещения Налево;\nНажмите D для перемещения Направо;\nНажмите Esc, чтобы выйти из теста\nНажмите Enter, чтобы выбрать Ответ;\n:";
					while (pressedButton != 97 && pressedButton != 100 && pressedButton != 13 && pressedButton != 27) {
						while (!_kbhit()) {};
						pressedButton = _getch();
					}
					switch (pressedButton) {
					case 100:
						posFocus = (posFocus + 1) % 4;
						system("cls");
						break;
					case 97:
						posFocus = (posFocus - 1) % 4;
						system("cls");
						break;
					default:
						break;
					}
				}
				if (pressedButton == 27) {
					this->tests[choose].setNumbStopped(i);
					break;
				}
				if (!strcmp(this->tests[choose].getExercises()[i].getVariants()[alreadyUsed[posFocus]], this->tests[choose].getExercises()[i].getVariants()[3])) {
					std::cout << std::endl << "Ответ Правильный +" << std::endl;
					this->tests[choose].incrementCorrectAnswers();
				}
				else std::cout << std::endl << "Ответ Неверный -" << std::endl;
				system("pause");
				system("cls");
			}
			if (!this->tests[choose].getNumbStopped()) {
				gotoxy(0, 0);
				std::cout << "Тест: \"" << this->tests[choose].getCategory()[0] << " " << this->tests[choose].getCategory()[1] << "\" пройден\nПравильных Ответов: " << this->tests[choose].getCorrectAnswers() << " из " << this->tests[choose].getExercises().size() << "\nТочность: " << 100 / this->tests[choose].getExercises().size() * this->tests[choose].getCorrectAnswers() << "%" << std::endl;
				system("pause");
				this->tests[choose].makeCompleted();
			}
			system("cls");
			this->saveTestsResult();
		}
	}
}
void User::checkResult() {
	size_t choose = vertical_menu(this->makeMenuOfTests(false), HORIZONTAL_POSITION::CENTER, VERTICAL_POSITION::CENTER, ALIGNMENT::CENTER);
	size_t countCompleted = 0;
	for (size_t i = 0; i < this->tests.size(); i++) {
		if (this->tests[i].getIsCompleted()) countCompleted++;
	}
	if (choose != -1 && choose != countCompleted) {
		vector<Test> completedTests;
		completedTests.resize(countCompleted);
		for (size_t i = 0, j = 0; i < this->tests.size(); i++) {
			if (this->tests[i].getIsCompleted()) {
				completedTests[j++] = this->tests[i];
			}
		}
		system("cls");
		gotoxy(0, 0);
		std::cout << "Тест: \"" << completedTests[choose].getCategory()[0] << " " << completedTests[choose].getCategory()[1] << "\"\nПравильные Ответы: " << completedTests[choose].getCorrectAnswers() << " из " << completedTests[choose].getExercises().size() << "\nТочность: " << 100 / completedTests[choose].getExercises().size() * completedTests[choose].getCorrectAnswers() << "%" << std::endl;
		system("pause");
	}
	system("cls");
}

User::User() {}
User::~User() {
	delete this->login;
	delete this->password;
	delete this->tel;
	tests.clear();
	for (size_t i = 0; i < 3; i++) delete this->fullName[i];
	delete[] this->fullName;
	for (size_t i = 0; i < 4; i++) delete this->ip[i];
	delete[] this->ip;
}
User::User(const User& obj) {
	equateString(this->login, obj.login);
	equateString(this->password, obj.login);
	for (size_t i = 0; i < 3; i++)
		equateString(this->fullName[i], obj.fullName[i]);
	for (size_t i = 0; i < 4; i++)
		equateString(this->ip[i], obj.ip[i]);
	equateString(this->tel, obj.tel);
	for (size_t i = 0; i < this->tests.size(); i++)
		this->tests.push_back(this->tests[i]);
}

void User::setLogin(const char* text) {
	equateString(this->login, text);
}
void User::setPassword(const char* text) {
	equateString(this->password, text);
}

void User::setName(const char* text) {
	equateString(this->fullName[0], text);
}
void User::setSurname(const char* text) {
	equateString(this->fullName[1], text);
}
void User::setPatronymic(const char* text) {
	equateString(this->fullName[2], text);
}

void User::setFirstPartIp(const char* text) {
	equateString(this->ip[0], text);
}
void User::setSecondPartIp(const char* text) {
	equateString(this->ip[1], text);
}
void User::setThirdPartIp(const char* text) {
	equateString(this->ip[2], text);
}
void User::setFourthPartIp(const char* text) {
	equateString(this->ip[3], text);
}

void User::setTel(const char* text) {
	equateString(this->tel, text);
}

const char* User::getLogin() const {
	return this->login;
}
const char* User::getPassword() const {
	return this->password;
}
const std::vector<Test> User::getTests() const {
	return this->tests;
}
const char* User::getTel() const {
	return this->tel;
}
char** User::getFullName() const {
	return this->fullName;
}
char** User::getIp() const {
	return this->ip;
}

void User::reg(bool save) {
	for (size_t i = 0; true; i++) {
		char buff[80];
		if (i != 0) system("cls");
		gotoxy(0, 0);
		std::cout << "Поле Регистрации:\n----" << UserParam_1 << ": ";

		std::cin >> buff;
		if (!save) {
			bool can = true;
			char buff2[80];
			ifstream in("users.txt");
			while (in >> buff2) {
				if (!strcmp(buff2, buff)) {
					can = false;
					break;
				}
				else {
					for (size_t j = 0; j < 6; j++) in >> buff2;
				}
			}
			if (!can) continue;
			if (can && strlen(buff) <= countCols - strlen(UserParam_1) - 7) {
				equateString(this->login, buff);
				break;
				in.close();
			}
		}
		if (strlen(buff) <= countCols - strlen(UserParam_1) - 7) {
			equateString(this->login, buff);
			break;
		}
	}

	for (size_t i = 0; true; i++) {
		char buff[80];
		if (i != 0) {
			system("cls");
			gotoxy(0, 0);
			std::cout << "Поле Регистрации:\n----" << UserParam_1 << ": " << this->login;
		}
		gotoxy(0, 2);
		std::cout << "----" << UserParam_2 << ": ";

		std::cin >> buff;
		if (strlen(buff) <= countCols - strlen(UserParam_2) - 7 && strlen(buff) >= 7) {
			equateString(this->password, buff);
			break;
		}
	}

	for (size_t i = 0; true; i++) {
		char buff[80];
		if (i != 0) {
			system("cls");
			gotoxy(0, 0);
			std::cout << "Поле Регистрации:\n----" << UserParam_1 << ": " << this->login << "\n----" << UserParam_2 << ": " << this->password;
		}
		gotoxy(0, 3);
		std::cout << "----" << UserParam_3 << ": Имя: ";

		std::cin >> buff;
		if (isAllSymbolsLetters(buff) && strlen(buff) <= 20) {
			equateString(this->fullName[0], buff);
			break;
		}
	}

	for (size_t i = 0; true; i++) {
		char buff[80];
		if (i != 0) {
			system("cls");
			gotoxy(0, 0);
			std::cout << "Поле Регистрации:\n----" << UserParam_1 << ": " << this->login << "\n----" << UserParam_2 << ": " << this->password << "\n----" << UserParam_3 << ": Имя: " << this->fullName[0];
		}
		else {
			gotoxy((strlen(UserParam_3) + strlen(this->fullName[0]) + 11) % countCols, 3 + int((strlen(UserParam_3) + strlen(this->fullName[0]) + 11) / countCols));
		}
		std::cout << " | Фамилия: ";

		std::cin >> buff;
		if (isAllSymbolsLetters(buff) && strlen(buff) <= 30) {
			equateString(this->fullName[1], buff);
			break;
		}
	}

	for (size_t i = 0; true; i++) {
		char buff[80];
		if (i != 0) {
			system("cls");
			gotoxy(0, 0);
			std::cout << "Поле Регистрации:\n----" << UserParam_1 << ":\n----" << UserParam_2 << ":\n----" << UserParam_3 << ": Имя: " << this->fullName[0] << " | Фамилия: " << this->fullName[1];
		}
		else {
			gotoxy((strlen(UserParam_3) + strlen(this->fullName[0]) + strlen(this->fullName[1]) + 23) % countCols, 3 + int((strlen(UserParam_3) + strlen(this->fullName[0]) + strlen(this->fullName[1]) + 24) / countCols));
		}
		std::cout << " | Отчество: ";

		std::cin >> buff;
		if (isAllSymbolsLetters(buff) && strlen(buff) <= 25) {
			equateString(this->fullName[2], buff);
			break;
		}
	}

	for (size_t i = 0; true; i++) {
		char buff[80];
		bool can = true;
		if (i != 0) {
			system("cls");
			gotoxy(0, 0);
			std::cout << "Поле Регистрации:\n----" << UserParam_1 << ": " << this->login << "\n----" << UserParam_2 << ": " << this->password << "\n----" << UserParam_3 << ": " << this->fullName[0] << " | " << this->fullName[1] << " | " << this->fullName[2];
		}
		gotoxy(0, 4);
		std::cout << "----" << UserParam_4 << ": ";

		std::cin >> buff;
		for (size_t j = 0; buff[j] != '\0'; j++) {
			if (!isSymbolDigit(buff[j]) && ((buff[j] == '+') ? (j != 0) : 1) && ((buff[j] == '-') ? buff[j + 1] == '-' : 1)) {
				can = false;
				break;
			}
		}
		if (can) {
			equateString(this->tel, buff);
			break;
		}
	}

	for (size_t i = 0, j = 0; j < 4; i++) {
		char buff[80];
		int countSomething = 0;
		if (i != 0) {
			system("cls");
			gotoxy(0, 0);
			std::cout << "Поле Регистрации:\n----" << UserParam_1 << ": " << this->login << "\n----" << UserParam_2 << ": " << this->password << "\n----" << UserParam_3 << ": " << this->fullName[0] << " | " << this->fullName[1] << " | " << this->fullName[2] << "\n----" << UserParam_4 << ": " << this->tel << std::endl;
		}
		else gotoxy(0, 5);
		std::cout << "----" << UserParam_5 << "(после каждого поля ставьте: \".\"(кроме последнего)): ";

		std::cin >> buff;
		for (size_t k = 0; buff[k] != '\0'; k++) {
			if ((!isdigit(buff[k]) && buff[k] != '.') || (buff[k] == '.' && (k == 0 || !isdigit(buff[k + 1]))) || (buff[k] == '0' && ((k == 0 && isdigit(buff[k + 1])) || ((k > 0 && k < strlen(buff)) ? !isdigit(buff[k - 1]) && isdigit(buff[k + 1]) : 0)))) {
				countSomething = 0;
				break;
			}
			if (buff[k] == '.') countSomething++;
		}
		if (countSomething == 3) {
			countSomething = 0;
			for (size_t k = 0, p = 0; buff[k] != '\0'; k++) {
				if (buff[k] != '.') countSomething += (buff[k] - 48) * pow(10, p++);
				if (buff[k] == '.' || buff[k + 1] == '\0') {
					p = 0;
					reverseNumber(countSomething);
					if (countSomething <= 255) {
						equateString(ip[j++], stringFromInt(countSomething));
					}
					else {
						j = 0;
						break;
					}
					countSomething = 0;
				}
			}
		}
	}

	this->loadTests();

	if (save) this->saveUser();

	system("pause");
	system("cls");
}

void User::saveUser() {
	std::ofstream out("users.txt");
	out << this->login << " " << this->password << " " << this->fullName[0] << " " << this->fullName[1] << " " << this->fullName[2] << " " << this->tel << " " << this->ip[0] << "." << this->ip[1] << "." << this->ip[2] << "." << this->ip[3] << std::endl;
	out.close();
}

void User::loadTests() {
	std::ifstream tests("tests.txt");
	if (tests.is_open()) {
		char buff[80];
		for (size_t i = 0; tests >> buff; i++) {
			Test test;
			size_t posLine;

			test.setSubject(buff);
			tests >> buff;
			posLine = getPosSymbol(buff, '_', 0);
			while (posLine != strlen(buff)) {
				buff[posLine] = ' ';
				posLine = getPosSymbol(buff, '_', posLine);
			}
			test.setTheme(buff);

			for (size_t j = 0; tests >> buff; j++) {
				if (!strcmp(buff, "end")) break;
				tests >> buff;
				posLine = getPosSymbol(buff, '_', 0);
				while (posLine != strlen(buff)) {
					buff[posLine] = ' ';
					posLine = getPosSymbol(buff, '_', posLine);
				}
				Exercise ex;
				ex.setQuestion(buff);
				tests >> buff;
				posLine = 0;
				ex.setFirstVariant(getSubstr(buff, posLine, getPosSymbol(buff, ',', posLine)));
				posLine = getPosSymbol(buff, ',', posLine) + 1;
				ex.setSecondVariant(getSubstr(buff, posLine, (getPosSymbol(buff, ',', posLine)) - posLine));
				posLine = getPosSymbol(buff, ',', posLine) + 1;
				ex.setThirdVariant(getSubstr(buff, posLine, (getPosSymbol(buff, ',', posLine)) - posLine));
				posLine = getPosSymbol(buff, ',', posLine) + 1;
				ex.setFourthVariant(getSubstr(buff, posLine, (getPosSymbol(buff, ',', posLine)) - posLine));

				test.addExercise(ex);
			}

			this->tests.push_back(test);
		}
	}
	tests.close();
}
void User::loadTestResult() {
	std::ifstream in("testResult.txt");
	if (in.is_open()) {
		char buff[80];
		while (in >> buff) {
			if (!strcmp(this->login, buff)) {
				in >> buff;
				bool allGood = false;
				for (size_t j = 0; j < this->tests.size(); j++) {
					if (!strcmp(buff, this->tests[j].getCategory()[0])) {
						char buff2[80];
						if (!j) in >> buff2;
						if (!strcmp(buff2, this->tests[j].getCategory()[1])) {
							in >> buff2;
							this->tests[j].setCorrectAnswers(intFromString(buff2));
							in >> buff2;
							if (!strcmp(buff2, "0")) {
								in >> buff2;
								this->tests[j].setNumbStopped(intFromString(buff2));
							}
							else {
								this->tests[j].makeCompleted();
							}
							allGood = true;
							break;
						}
					}
				}
				if (!allGood) in >> buff;
			}
		}
	}
	in.close();
}

void User::interact() {
	{
		ifstream in("users.txt");
		char buff[80];
		if (in >> buff) this->signIn();
		else this->reg();
		in.close();
	}

	char** userMenu1 = new char* [3];
	userMenu1[0] = new char[] {" Пройти Тест "};
	userMenu1[1] = new char[] {" Посмотреть Результаты "};
	userMenu1[2] = new char[] {" Выйти "};
	char** userMenu2 = new char* [2];
	userMenu2[0] = new char[] {" Пройти Тест "};
	userMenu2[1] = new char[] {" Выйти "};

	size_t choose;
	bool haveCompleted = false;
	do {
		for (size_t i = 0; i < this->tests.size(); i++) {
			if (this->tests[i].getIsCompleted()) haveCompleted = true;
		}
		choose = vertical_menu(((haveCompleted) ? userMenu1 : userMenu2), HORIZONTAL_POSITION::CENTER, VERTICAL_POSITION::CENTER, ALIGNMENT::CENTER);
		switch (choose) {
		case 0:
			this->passTest();
			break;
		case 1:
			if (haveCompleted) this->checkResult();
			break;
		}
	} while (choose != -1 && ((choose != 1 && !haveCompleted) || (choose != 2 && haveCompleted)));

	for (size_t i = 0; i < 3; i++) {
		delete userMenu1[i];
		if (i < 2) delete userMenu2[i];
	}
	delete[] userMenu1;
	delete[] userMenu2;
}

class Admin {
	char* login = nullptr;
	char* password = nullptr;
	vector<User> users;
	vector<Test> tests;

	void saveUsers() const;
	void saveTests() const;

	void loadUsers();
	void loadTests();

	size_t getIndexOfUser(const char* text, bool needUser);

	void addUser();
	void addTest();
	void editUser();
	void deleteUser();
	void deleteTest();
public:
	Admin();
	~Admin();

	void interact();
};

void Admin::saveUsers() const {
	ofstream out("users.txt");
	for (size_t i = 0; i < users.size(); i++) out << this->users[i].getLogin() << " " << this->users[i].getPassword() << " " << this->users[i].getFullName()[0] << " " << this->users[i].getFullName()[1] << " " << this->users[i].getFullName()[2] << " " << this->users[i].getTel() << " " << this->users[i].getIp()[0] << "." << this->users[i].getIp()[1] << "." << this->users[i].getIp()[2] << "." << this->users[i].getIp()[3] << std::endl;
	out.close();
}
void Admin::saveTests() const {
	ofstream out("tests.txt");
	for (size_t i = 0; i < this->tests.size(); i++) {
		out << replaceSpaceOnLines(this->tests[i].getCategory()[0]) << " " << replaceSpaceOnLines(this->tests[i].getCategory()[1]) << "\n";
		for (size_t j = 0; j < this->tests[i].getExercises().size(); j++) {
			out << j << " " << replaceSpaceOnLines(this->tests[i].getExercises()[j].getQuestion()) << " " << replaceSpaceOnLines(this->tests[i].getExercises()[j].getVariants()[0]) << "," << replaceSpaceOnLines(this->tests[i].getExercises()[j].getVariants()[1]) << "," << replaceSpaceOnLines(this->tests[i].getExercises()[j].getVariants()[2]) << "," << replaceSpaceOnLines(this->tests[i].getExercises()[j].getVariants()[3]) << ((j + 1 == this->tests[i].getExercises().size()) ? "\n" : "end\n");
		}
	}
	out.close();
}

void Admin::loadUsers() {
	std::ifstream in("users.txt");
	char buff[80];
	for (size_t i = 0; in >> buff; i++) {
		User us;
		us.setLogin(buff);
		in >> buff;
		us.setPassword(buff);
		in >> buff;
		us.setName(buff);
		in >> buff;
		us.setSurname(buff);
		in >> buff;
		us.setPatronymic(buff);
		in >> buff;
		us.setTel(buff);
		in >> buff;
		{
			char* ipStr = nullptr;
			equateString(ipStr, buff, getPosSymbol(buff, '.'), 0);
			us.setFirstPartIp(ipStr);
			equateString(ipStr, buff, getPosSymbol(buff, '.', getPosSymbol(buff, '.') + 1) - getPosSymbol(buff, '.') - 1, getPosSymbol(buff, '.') + 1);
			us.setSecondPartIp(ipStr);
			equateString(ipStr, buff, getPosSymbol(buff, '.', getPosSymbol(buff, '.', getPosSymbol(buff, '.') + 1) + 1) - (getPosSymbol(buff, '.', getPosSymbol(buff, '.') + 1) - getPosSymbol(buff, '.')) - getPosSymbol(buff, '.') - 1, getPosSymbol(buff, '.', getPosSymbol(buff, '.') + 1) + 1);
			us.setThirdPartIp(ipStr);
			equateString(ipStr, buff, strlen(buff) - (getPosSymbol(buff, '.', getPosSymbol(buff, '.', getPosSymbol(buff, '.') + 1) + 1) - (getPosSymbol(buff, '.', getPosSymbol(buff, '.') + 1) - getPosSymbol(buff, '.')) - getPosSymbol(buff, '.')) - (getPosSymbol(buff, '.', getPosSymbol(buff, '.') + 1) - getPosSymbol(buff, '.')) - getPosSymbol(buff, '.') - 1, getPosSymbol(buff, '.', getPosSymbol(buff, '.', getPosSymbol(buff, '.') + 1) + 1) + 1);
			us.setFourthPartIp(ipStr);
		}
		us.loadTests();
		us.loadTestResult();
		this->users.push_back(us);
	}
}
void Admin::loadTests() {
	std::ifstream tests("tests.txt");
	if (tests.is_open()) {
		char buff[80];
		for (size_t i = 0; tests >> buff; i++) {
			Test test;
			size_t posLine;

			test.setSubject(buff);
			tests >> buff;
			posLine = getPosSymbol(buff, '_', 0);
			while (posLine != strlen(buff)) {
				buff[posLine] = ' ';
				posLine = getPosSymbol(buff, '_', posLine);
			}
			test.setTheme(buff);

			for (size_t j = 0; tests >> buff; j++) {
				if (!strcmp(buff, "end")) break;
				tests >> buff;
				posLine = getPosSymbol(buff, '_', 0);
				while (posLine != strlen(buff)) {
					buff[posLine] = ' ';
					posLine = getPosSymbol(buff, '_', posLine);
				}
				Exercise ex;
				ex.setQuestion(buff);
				tests >> buff;
				posLine = 0;
				ex.setFirstVariant(getSubstr(buff, posLine, getPosSymbol(buff, ',', posLine)));
				posLine = getPosSymbol(buff, ',', posLine) + 1;
				ex.setSecondVariant(getSubstr(buff, posLine, (getPosSymbol(buff, ',', posLine)) - posLine));
				posLine = getPosSymbol(buff, ',', posLine) + 1;
				ex.setThirdVariant(getSubstr(buff, posLine, (getPosSymbol(buff, ',', posLine)) - posLine));
				posLine = getPosSymbol(buff, ',', posLine) + 1;
				ex.setFourthVariant(getSubstr(buff, posLine, (getPosSymbol(buff, ',', posLine)) - posLine));

				test.addExercise(ex);
			}

			this->tests.push_back(test);
		}
	}
}

size_t Admin::getIndexOfUser(const char* text, bool needUser) {
	char buff[80];
	do {
		if (((needUser) ? this->users.size() > 0 : this->tests.size() > 0)) {
			gotoxy(0, 0);
			for (size_t i = 0; i < ((needUser) ? this->users.size() : this->tests.size()); i++) {
				std::cout << i + 1 << ") " << ((needUser) ? this->users[i].getLogin() : this->tests[i].getCategory()[0]) << ((needUser) ? "" : " ") << ((needUser) ? "" : this->tests[i].getCategory()[1]) << std::endl;
			}
			std::cout << text;
			cin >> buff;
			system("cls");
		}
	} while (((isAllSymbolsDigit(buff)) ? intFromString(buff) <= 0 || ((needUser) ? intFromString(buff) > this->users.size() : intFromString(buff) > this->tests.size()) : 1));
	return (intFromString(buff) - 1);
}

void Admin::addUser() {
	User us;
	us.reg(false);
	this->users.push_back(us);
	this->saveUsers();
}
void Admin::addTest() {
	Test t;
	for (size_t i = 0; true; i++) {
		char buff[80];
		if (i) std::system("cls");
		gotoxy(0, 0);
		std::cout << "Добавить Тест:\n----Раздел: ";

		std::cin >> buff;
		if (isAllSymbolsLetters(buff)) {
			t.setSubject(buff);
			break;
		}
	}
	for (size_t i = 0; true; i++) {
		char buff[80];
		if (i) std::system("cls");
		gotoxy(0, 0);
		std::cout << "Добавить Тест:\n----Раздел: " << t.getCategory()[0] << "\n----Тема: ";

		std::cin >> buff;
		if (isAllSymbolsLetters(buff)) {
			t.setTheme(buff);
			std::system("cls");
			break;
		}
	}
	char** testMenu = new char* [2];
	testMenu[0] = new char[] {" Добавить Неправильный Вариант "};
	testMenu[1] = new char[] {" Добавить Правильный Вариант "};
	int pressedButton = 0;
	for (size_t i = 0; pressedButton != 27; i++) {
		char buff[80];
		size_t choose;
		Exercise ex;
		bool chooseEqualedOne = false;
		gotoxy(0, 0);
		std::cout << "Добавить Тест:\n----Раздел: " << t.getCategory()[0] << "\n----Тема: " << t.getCategory()[1] << "\n----" << i + 1 << " Задание:\n--------Вопрос: ";
		std::cin >> buff;
		ex.setQuestion(buff);
		for (size_t j = 0; j < 3 || !chooseEqualedOne; ) {
			system("cls");
			gotoxy(0, 0);
			std::cout << "Добавить Тест:\n----Раздел: " << t.getCategory()[0] << "\n----Тема: " << t.getCategory()[1] << "\n----" << i + 1 << " Задание:\n--------Вопрос: " << ex.getQuestion();
			if (j < 3 && !chooseEqualedOne) {
				std::cout << "\n--------Выберите Опцию:";
				do {
					choose = vertical_menu(testMenu, strlen("--------Выберите Опцию:"), 5, ALIGNMENT::CENTER);
				} while (choose == -1);
			}
			if (!choose) {
				gotoxy(strlen(((!chooseEqualedOne) ? "--------Выберите Опцию:" : "")), 5);
				std::cout << ((!chooseEqualedOne) ? testMenu[choose] : "") << ((!chooseEqualedOne) ? "\n" : "") << "--------Введите Неправильный Ответ: ";
				std::cin >> buff;
				switch (j) {
				case 0:
					ex.setFirstVariant(buff);
					break;
				case 1:
					ex.setSecondVariant(buff);
					break;
				case 2:
					ex.setThirdVariant(buff);
					choose = 1;
					j++;
					continue;
				}
				j++;
			}
			if (choose) {
				gotoxy(strlen(((j < 3) ? "--------Выберите Опцию:" : "")), 5);
				std::cout << ((j < 3) ? testMenu[choose] : "") << ((j < 3) ? "\n" : "") << "--------Введите Правильный Ответ: ";
				std::cin >> buff;
				ex.setFourthVariant(buff);
				chooseEqualedOne = true;
				choose = 0;
			}
		}
		t.addExercise(ex);
		std::cout << "Если Хотите Выйти, Нажмите Esc\nЕсли Хотите продолжить, Нажмите Enter";
		pressedButton = 0;
		while (pressedButton != 13 && pressedButton != 27) {
			while (!_kbhit()) {};
			pressedButton = _getch();
		}
		system("cls");
	}
	this->tests.push_back(t);
	this->saveTests();
	for (size_t i = 0; i < 2; i++) delete testMenu[i];
	delete[] testMenu;
}
void Admin::editUser() {
	size_t userPos = this->getIndexOfUser("Введите Номер Редактируемого Пользователя: ", true);
	size_t choose;
	char** menuParamsToEdit = new char* [8];
	menuParamsToEdit[0] = new char[] {" Логин "};
	menuParamsToEdit[1] = new char[] {" Пароль "};
	menuParamsToEdit[2] = new char[] {" Имя "};
	menuParamsToEdit[3] = new char[] {" Фамилия "};
	menuParamsToEdit[4] = new char[] {" Отчество "};
	menuParamsToEdit[5] = new char[] {" Телефонный Номер "};
	menuParamsToEdit[6] = new char[] {" IP "};
	menuParamsToEdit[7] = new char[] {" Выйти "};
	do {
		choose = vertical_menu(menuParamsToEdit, HORIZONTAL_POSITION::CENTER, VERTICAL_POSITION::CENTER, ALIGNMENT::CENTER);
		switch (choose) {
		case 0:
			do {
				char buff[80];
				system("cls");
				gotoxy(0, 0);
				std::cout << "Новый Логин: ";

				std::cin >> buff;

				bool can = true;
				char buff2[80];
				ifstream in("users.txt");
				while (in >> buff2) {
					if (!strcmp(buff2, buff)) {
						can = false;
						break;
					}
					else {
						for (size_t j = 0; j < 6; j++) in >> buff2;
					}
				}
				if (!can) continue;
				if (strlen(buff) <= countCols - strlen(UserParam_1) - 7) {
					this->users[userPos].setLogin(buff);
					in.close();
					break;
				}
			} while (true);
			break;
		case 1:
			do {
				char buff[80];
				system("cls");
				gotoxy(0, 0);
				std::cout << "Новый Пароль";

				std::cin >> buff;
				if (strlen(buff) <= countCols - strlen(UserParam_2) - 7 && strlen(buff) >= 7) {
					this->users[userPos].setPassword(buff);
					break;
				}
			} while (true);
			break;
		case 2:
			do {
				char buff[80];
				system("cls");
				gotoxy(0, 0);
				std::cout << "Новое Имя: ";

				std::cin >> buff;
				if (isAllSymbolsLetters(buff) && strlen(buff) <= 20) {
					this->users[userPos].setName(buff);
					break;
				}
			} while (true);
			break;
		case 3:
			do {
				char buff[80];
				system("cls");
				gotoxy(0, 0);
				std::cout << "Новая Фамилия: ";

				std::cin >> buff;
				if (isAllSymbolsLetters(buff) && strlen(buff) <= 30) {
					this->users[userPos].setSurname(buff);
					break;
				}
			} while (true);
			break;
		case 4:
			for (size_t i = 0; true; i++) {
				char buff[80];
				system("cls");
				gotoxy(0, 0);
				std::cout << "Новое Отчество: ";

				std::cin >> buff;
				if (isAllSymbolsLetters(buff) && strlen(buff) <= 25) {
					this->users[userPos].setPatronymic(buff);
					break;
				}
			}
			break;
		case 5:
			do {
				char buff[80];
				bool can = true;
				system("cls");
				gotoxy(0, 0);
				std::cout << "Новый Номер Телефона: ";

				std::cin >> buff;
				for (size_t j = 0; buff[j] != '\0'; j++) {
					if (!isSymbolDigit(buff[j]) && ((buff[j] == '+') ? (j != 0) : 1) && ((buff[j] == '-') ? buff[j + 1] == '-' : 1)) {
						can = false;
						break;
					}
				}
				if (can) {
					this->users[userPos].setTel(buff);
					break;
				}
			} while (true);
			break;
		case 6:
			for (size_t j = 0; j < 4;) {
				char buff[80];
				int countSomething = 0;
				system("cls");
				gotoxy(0, 0);
				std::cout << "Новое IP(после каждого поля ставьте: \".\"(кроме последнего)): ";

				std::cin >> buff;
				for (size_t o = 0; buff[o] != '\0'; o++) {
					if ((!isdigit(buff[o]) && buff[o] != '.') || (buff[o] == '.' && (o == 0 || !isdigit(buff[o + 1]))) || (buff[o] == '0' && ((o == 0 && isdigit(buff[o + 1])) || ((o > 0 && o < strlen(buff)) ? !isdigit(buff[o - 1]) && isdigit(buff[o + 1]) : 1)))) {
						countSomething = 0;
						break;
					}
					if (buff[o] == '.') countSomething++;
				}
				if (countSomething == 3) {
					countSomething = 0;
					for (size_t k = 0, p = 0; buff[k] != '\0'; k++) {
						if (buff[k] != '.') {
							countSomething += (buff[k] - 48) * pow(10, p++);
						}
						if (buff[k] == '.' || buff[k + 1] == '\0') {
							p = 0;
							reverseNumber(countSomething);
							if (countSomething <= 255) {
								switch (j) {
								case 0:
									this->users[userPos].setFirstPartIp(stringFromInt(countSomething));
									break;
								case 1:
									this->users[userPos].setSecondPartIp(stringFromInt(countSomething));
									break;
								case 2:
									this->users[userPos].setThirdPartIp(stringFromInt(countSomething));
									break;
								case 3:
									this->users[userPos].setFourthPartIp(stringFromInt(countSomething));
									break;
								}
								j++;
							}
							else {
								j = 0;
								break;
							}
							countSomething = 0;
						}
					}
				}
			}
			break;
		}
		system("cls");
	} while (choose != -1 && choose != 7);
	this->saveUsers();

	for (size_t i = 0; i < 8; i++) delete menuParamsToEdit[i];
	delete[] menuParamsToEdit;
}
void Admin::deleteUser() {
	this->users.erase(this->users.begin() + this->getIndexOfUser("Введите Номер Удаляемого Пользователя: ", true));
	ofstream out("testResult.txt");
	for (size_t i = 0; i < this->users.size(); i++) {
		for (size_t j = 0; j < this->users[i].getTests().size(); j++) {
			if (this->users[i].getTests()[j].getIsCompleted() || this->users[i].getTests()[j].getNumbStopped()) {
				out << this->users[i].getLogin() << " " << this->users[i].getTests()[j].getCategory()[0] << " " << this->users[i].getTests()[j].getCategory()[1] << " " << this->users[i].getTests()[j].getCorrectAnswers() << " " << this->users[i].getTests()[j].getIsCompleted() << ((this->users[i].getTests()[j].getIsCompleted()) ? "" : " ") << ((this->users[i].getTests()[j].getIsCompleted()) ? "" : stringFromInt(this->users[i].getTests()[j].getNumbStopped())) << std::endl;
			}
		}
	}
	out.close();
	this->saveUsers();
}
void Admin::deleteTest() {
	this->tests.erase(this->tests.begin() + this->getIndexOfUser("Введите Номер Удаляемого Теста: ", false));
	this->saveTests();
}

Admin::Admin() {}
Admin::~Admin() {
	this->tests.clear();
	this->users.clear();
}

void Admin::interact() {
	this->loadUsers();
	this->loadTests();

	char** adminMenu = new char* [6];
	adminMenu[0] = new char[] {" Добавить Пользователя "};
	adminMenu[1] = new char[] {" Редактировать Пользователя "};
	adminMenu[2] = new char[] {" Удалить Пользователя "};
	adminMenu[3] = new char[] {" Добавить Тест "};
	adminMenu[4] = new char[] {" Удалить Тест "};
	adminMenu[5] = new char[] {" Выйти "};

	size_t choose;
	do {
		choose = vertical_menu(adminMenu, HORIZONTAL_POSITION::CENTER, VERTICAL_POSITION::CENTER, ALIGNMENT::CENTER);
		system("cls");
		if (!choose) this->addUser();
		if (choose == 1 && this->users.size() > 0) this->editUser();
		if (choose == 2 && this->users.size() > 0) this->deleteUser();
		if (choose == 3) this->addTest();
		if (choose == 4) this->deleteTest();
	} while (choose != -1 && choose != 2);

	for (size_t i = 0; i < 6; i++) delete adminMenu[i];
	delete[] adminMenu;
}

class TestBase {
public:
	TestBase();
	~TestBase();

	void interact();
};

TestBase::TestBase() {}
TestBase::~TestBase() {

}

void TestBase::interact() {
	char** mainMenu = new char* [3];
	mainMenu[0] = new char[] {" Войти в режим Админа "};
	mainMenu[1] = new char[] {" Войти в режим Пользователя "};
	mainMenu[2] = new char[] {" Выйти"};

	size_t choose;
	do {
		choose = vertical_menu(mainMenu, HORIZONTAL_POSITION::CENTER, VERTICAL_POSITION::CENTER, ALIGNMENT::CENTER);
		if (!choose) {
			Admin ad;
			ad.interact();
		}
		if (choose == 1) {
			User ad;
			ad.interact();
		}
	} while (choose != -1 && choose != 2);
}