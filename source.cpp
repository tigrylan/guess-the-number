#include<iostream>
#include<string>
#include<ctime>
using namespace std;

string strGameOver = R"(
		  ________    _____      _____  ___________ ____________   _________________________ 
		 /  _____/   /  _  \    /     \ \_   _____/ \_____  \   \ /   /\_   _____/\______   \
		/   \  ___  /  /_\  \  /  \ /  \ |    __)_   /   |   \   Y   /  |    __)_  |       _/
		\    \_\  \/    |    \/    Y    \|        \ /    |    \     /   |        \ |    |   \
		 \______  /\____|__  /\____|__  /_______  / \_______  /\___/   /_______  / |____|_  /
                \/         \/         \/        \/          \/                 \/         \/ 
)";

string strAiWin = R"(               _____    __          __  _____   _   _   _ 
       /\     |_   _|   \ \        / / |_   _| | \ | | | |
      /  \      | |      \ \  /\  / /    | |   |  \| | | |
     / /\ \     | |       \ \/  \/ /     | |   | . ` | | |
    / ____ \   _| |_       \  /\  /     _| |_  | |\  | |_|
   /_/    \_\ |_____|       \/  \/     |_____| |_| \_| (_))";

int getUserInputNumber(const string& message, const int& MIN, const int& MAX)
{
	int number;
	while (true) // Бесконечный цикл, который внутри прерывается по условию
	{
		cout << message; // Вывод сообщения для пользователя
		cin >> number;   // Ввод значения пользователем
		if (!cin.fail()) // Если ввели число, а значит поток не в состоянии ошибки, то завершаем цикл
		{
			if (number < MIN)
			{
				cout << "		number too small" << endl;
				continue;
			}
			if (number > MAX)
			{
				cout << "		number too big" << endl;
				continue;
			}
			break;
		}
		cout << "		syntax error" << endl;
		cin.clear(); // Сбрасываем состояние ошибки
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	}
	return number; // Возвращаем из функции результат в место вызова функции
}

int checkUserInputMode()
{
	int mode;
	while (true) // Бесконечный цикл, который внутри прерывается по условию
	{
		cin >> mode;   // Ввод значения пользователем
		if (!cin.fail()) // Если ввели число, а значит поток не в состоянии ошибки, то завершаем цикл
		{
			if (mode == 2 || mode == 1)
			{
				break;
			}
			else continue;
		}
		cout << "		syntax error" << endl;
		cin.clear(); // Сбрасываем состояние ошибки
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	}
	return mode;
}
char getInputAnswer()
{
	char mode;
	while (true) // Бесконечный цикл, который внутри прерывается по условию
	{
		cin >> mode;   // Ввод значения пользователем
		if (!cin.fail()) // Если ввели число, а значит поток не в состоянии ошибки, то завершаем цикл
		{
			if (mode == 'y' || mode == 'n' || mode == 't')
			{
				break;
			}
			else continue;
		}
		cout << "		syntax error" << endl;
		cin.clear(); // Сбрасываем состояние ошибки
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	}
	return mode;
}
int main() {
	setlocale(LC_ALL, "Rus");
	srand(time(0));
	const int MAX = 1000;
	const int MIN = 1;
	const string messageTask =
		R"(					 Игра «Угадай число»
		 _______________________________________________________________
		| Один из играющих задумывает число от 1 до 1000,               |
		| а другой пытается угадать его за 10 вопросов вида: верно ли,  |
		| что задуманное число больше такого - то числа.                |
		|_______________________________________________________________|)";
	const string messageForFirstPlayer = R"(
		 __________________________________________
		|Загадайте число в диапазоне от 1 до 1000: |
		|__________________________________________|
)";
	const string messageForSecondPlayer = R"(
		 ___________________________________________________
		|Попробуйте угадать число в диапазоне от 1 до 1000: |
		|___________________________________________________|
)";

	while (true)
	{
		int mode;
		int countQuestions = 10;
		cout << messageTask << endl;// условие задачи
		cout << endl <<
			R"(		 _____________________
		|Выберите режим игры: |
		|1 - с компьютером    |
		|2 - с игроком        |
		|_____________________|)" << endl;
		mode = checkUserInputMode();// проверка правильности ввода числа 1 или 2 для режима игры
		if (mode == 1)// с ИИ
		{
			char answer;
			int priorityPlayer = rand() % 2 + 1;
			cout << R"(		 _____________________________
		| Игра автоматически выбирет, |
		| кто будет первый ходить     |
		|_____________________________|)" << endl;
			if (priorityPlayer == 1)//режим игры, в первом случае число загадывает игрок
			{
				cout << R"(		 ____________________________
		|Вам необходимо ввести число |
		|____________________________|)";
				int number = getUserInputNumber(messageForFirstPlayer, MIN, MAX); // проверка на попадание значения в диапазон и числовой принадлежности
				system("cls");
				cout << R"(		 
         ____________________________
		| Ответ указывать в виде y/n |
		| y - да                     |
		| n - нет                    |
		| t - загаданное число       |
		|____________________________|)" << endl;
				int numberGuess = (MAX - MIN + 1) / 2;
				int tmpMax = MAX, tmpMin = MIN;
				while (true)
				{
					cout << "		Задуманное чиcло больше, чем " << numberGuess << "?" << endl;
					answer = getInputAnswer();
					if (answer == 'n')
					{
							tmpMax = numberGuess;
							numberGuess -= (tmpMax - tmpMin + 1) / 2;
					}
					if (answer == 'y')
					{
						tmpMin = numberGuess;
						numberGuess += (tmpMax - tmpMin + 1) / 2;
					}
					if (answer == 't')
					{
						system("cls");
						cout << strAiWin;
						system("pause");
						break;
					}
					if (countQuestions <= 0)
					{
						system("cls");
						cout << "Кто то пытается обмануть систему, но был вовремя остановлен, поэтому угадываем сначала";
						system("pause");
						countQuestions = 11;
					}
					countQuestions--;
				}
			}
			else //число загадывает компьютер
			{
				int number = rand() % 1000 + 1;
				int numberGuess;
				cout << R"(		 _____________________________
		| Число загадывает компьютер |
		|____________________________|)" << endl;
				while (true)
				{
					if (countQuestions == 0)
					{
						cout << R"(		 _________
		|you lost |
		|_________|)";
						cout << "		Правильный ответ: " << number << endl;
						break;
					}
					if (countQuestions == 3)
					{
						cout << R"(		 ____________________________
		| У вас осталось 3 попытки!  |
		|____________________________|)" << endl;
					}
					cout << "		Задуманное чиcло больше, чем ";
					cin >> numberGuess;
					if (number < numberGuess)
					{
						cout << "Нет" << endl;
					}
					else
						if (number > numberGuess)
						{
							cout << "Да" << endl;
						}
						else
						{
							cout << R"(		 ____________________________
		|Вы угадали загаданное число |
		|____________________________|)";
							break;
						}
					countQuestions--;
				}
			}
		}
		else // 2 игрока
		{
			int number = getUserInputNumber(messageForFirstPlayer, MIN, MAX); // проверка на попадание значения в диапазон и числовой принадлежности
			system("cls");
			cout << R"(		
		/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
		< Теперь второй игрок отгадывает число >
		\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/)";
			cout << messageForSecondPlayer;
			int numberGuess;
			while (true)
			{
				if (countQuestions == 0)
				{
					cout << strGameOver;
					cout << "		Правильный ответ: " << number << endl;
					break;
				}
				if (countQuestions == 3)
				{
					cout << R"(		 ____________________________
		| У вас осталось 3 попытки!  |
		|____________________________|)" << endl;
				}
				numberGuess = getUserInputNumber("", MIN, MAX);
				if (numberGuess == number)
				{
					cout << R"(
		 _______________
		|Все правильно! |
		|_______________|)" << endl;
					cout << R"(
       __          __  _____   _   _ 
       \ \        / / |_   _| | \ | |
        \ \  /\  / /    | |   |  \| |
         \ \/  \/ /     | |   | . ` |
          \  /\  /     _| |_  | |\  |
           \/  \/     |_____| |_| \_|)" << endl;
					break;
				}
				if (numberGuess > number)
				{
					cout << R"(		 _________________________
		|       Не угадали        |
		|Загаданное число меньше  |
		|_________________________|)" << endl;
				}
				else
				{
					cout << R"(		 _________________________
		|       Не угадали        |
		|Загаданное число больше  |
		|_________________________|)" << endl;
				}
				countQuestions--;
			}
		}
		string gamePlay;
		cout << R"(
		 ____________________________________________
		|Для продолжения игры нажмите любой символ.  |
		|Для выхода из игры напишите: exit           |
		|____________________________________________|)" << endl;
		cin >> gamePlay;
		if (gamePlay == "exit")break;
	}
	return 0;
}


