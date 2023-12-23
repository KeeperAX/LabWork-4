#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <sstream>
using namespace std;
void searchWords(string& text);
void KMP(string& text) {
	cout << "Введите подстроку.\n";
	string podStr;
	getline(cin, podStr);
	system("cls");
	cout << "Строка.\n" << text << endl;
	int p;
	int table[100];
	string s1, s2;
	for (int i = 0; i < podStr.length(); i++)
	{
		s1.clear();
		s2.clear();
		int c = 0;
		for (int j = 0; j < i; j++)
		{
			s1 += podStr[j];
			s2.insert(0, 1, podStr[i]);
			p = s1.compare(s2);
			if (p == 0)
			{
				c++;
			}
		}
		table[i] = c;
	}
	int l = 0;
	for (int i = 0; i < text.length(); i++)
	{
		bool m = true;
		for (int j = 0; j < podStr.length(); j++)
		{
			if (text[i + j] != podStr[j])
			{
				i += j;
				i -= table[j];
				m = false;
				break;
			}
		}
		if (m)
		{
			cout << "\nПодстрока найдна на позиции: " << i + 1 << endl;
			l++;
		}
	}
	if (l == 0)
	{
		cout << "Подстрока не найдена\n";
	}

}
void lineSearch(string& text) {
	cout << "Введите подстроку.\n";
	string podStr;
	cin >> podStr;
	int size = text.size();
	system("cls");
	cout << "Строка.\n" << text << endl;
	for (int i = 0; i < size; i++) {
		if (text[i] == podStr[0]) {
			short start = i, end = i;
			int sizePod = podStr.size();
			string newStr;
			for (int j = i; j < i + sizePod; j++) {
				newStr += text[j];
			}
			for (int i = 0; i < sizePod; i++) {
				if (newStr[i] == podStr[i]) {
					end++;
				}
			}
			cout << "Слово находится в диапазоне от " << start << " до " << end << endl;
		}
	}
	searchWords(text);
}
void searchWords(string& text) {
	text = text;
	cout << "Выберите способ поиска подстроки:\n[1] Линейный.\n[2] КМП\n"; 
	int choice;
	cin >> choice;
	
	if (choice == 1)
	{
		lineSearch(text);
	}
	else if (choice == 2) {
		KMP(text);
	}
	
}
void vertText(string& text) {
	system("cls");
	cout << "Вертикальный текст\n";
	istringstream iss(text);
	string token;
	while (iss >> token) {
		cout << token << endl;
	}
}
void reverseText(string& text, string& oldText) {
	system("cls");
	cout << "Текст в обратном порядке.\n";
	reverse(text.begin(), text.end());
	auto textbegin = text.begin();
	auto textend = text.end();
	while (textbegin != text.end()) {
		while (textbegin != text.end() && isspace(*textbegin)) {
			textbegin++;
		}
		textend = textbegin;
		while (textend != text.end() && ! isspace(*textend)) {
			textend++;
		}
		reverse(textbegin, textend);
		textbegin = textend;
	}
	cout << text << endl;
	system("pause");
	vertText(oldText);
	searchWords(oldText);

}

void editText(string& text) {
	string OldText = text;;
	system("cls");
	cout << "\tОбычный текст.\n";
	cout << text;
	int ind = 0;
	int size = text.size();
	while (ind < size) {
		if (ind < size - 1 && (text[ind] == text[ind + 1] && text[ind] == ' ')) {
			text.replace(ind, 1, "");
			size--;
		}
		else if (ind + 3 < size && text[ind] == '.' && text[ind + 1] == '.' && text[ind + 2] == '.' && text[ind + 3] == ' ') {
			ind += 3;
		}
		else if (ind < size - 1 && ispunct(text[ind]) && ispunct(text[ind + 1])) {
			text.replace(ind + 1, 1, "");
			size--;
		}
		else {
			ind++;
		}
	}
	text[0] = toupper(text[0]);
	for (int i = 1; i < size; i++) {
		if (ispunct(text[i]) && i + 1 < size) {
			char nextChar = text[i + 1];
			if (nextChar == ' ' && i + 2 < size) {
				char charAfterSpace = text[i + 2];
				if (charAfterSpace != ',' && charAfterSpace != ':' && charAfterSpace != ';') {
					text[i + 2] = toupper(text[i + 2]);
					i += 2; 
				}
			}
		}
		else {
			text[i] = tolower(text[i]);
		}
	}
	cout << "\n\n\tИзменненый текст.\n";
	cout << text << endl;
	system("pause");
	reverseText(text, OldText);
}
void keyboardInput() {
	system("cls");
	cout << "Введи текст до 50 символов.\n";
	string text;
	cin.ignore(); // Игнорируем символ новой строки после выбора способа ввода
	getline(cin, text);
	editText(text);
}
void fileInput() {
	string text;
	cout << "Файл по умалчанию <LabWork4.text>.\nЖелаете работать в этом файле?\n[1] Да.\n[2] Нет.\n";
	int choice;
	cin >> choice;
	if (choice == 1){
		ifstream inputFile;
		inputFile.open("LabWork4.txt");
		if (!inputFile.is_open()) {
			cerr << "Ошибка открытия файла!" << endl;
			return;
		}
		getline(inputFile, text);
		editText(text);
	}
	else if (choice == 2) {
		string fileName;
		cout << "Введите название файла (формат файла txt): ";
		cin >> fileName;
		ifstream inputFile(fileName + ".txt");
		if (!inputFile.is_open()) {
			cerr << "Ошибка открытия файла!" << endl;
			return;
		}
		getline(inputFile, text);
		editText(text);
	}
	else {
		system("cls");
		fileInput();
	}
}
int main()
{
	setlocale(LC_ALL, "Russian");
	int choice;
	cout << "Выберите способ ввода:\n[1] С клавиатуру.\n[2] С файла.\n";
	cin >> choice;
	switch (choice)
	{
	case 1: keyboardInput(); break;
	case 2: fileInput(); break;
	default: system("cls"); return 1;
	}
	return 0;
}


