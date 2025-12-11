#include <Windows.h>

#include <iostream>

#include "binary_processor.h"

using namespace std;

// Функция для установки русской локали
void SetRussianLocale() {
  SetConsoleOutputCP(1251);
  SetConsoleCP(1251);
  setlocale(LC_ALL, "Russian");
}

void ShowMenu() {
  cout << "\n=== ГЛАВНОЕ МЕНЮ ===" << endl;
  cout << "1. Работа с бинарными числовыми данными (Задания 1 и 2)" << endl;
  cout << "2. Работа с багажом (Задание 3)" << endl;
  cout
      << "3. Работа с текстовыми данными - по одному числу в строке (Задание 4)"
      << endl;
  cout
      << "4. Работа с текстовыми данными - несколько чисел в строке (Задание 5)"
      << endl;
  cout << "5. Работа с текстовыми данными - строки (Задание 6)" << endl;
  cout << "0. Выход" << endl;
  cout << "Выбор: ";
}

void NumbersMenu() {
  string filename;
  cout << "Введите имя файла для числовых данных: ";
  cin >> filename;

  while (true) {
    cout << "\n=== МЕНЮ ЧИСЛОВЫХ ДАННЫХ ===" << endl;
    cout << "1. Заполнить файл случайными числами" << endl;
    cout << "2. Показать десятичное содержимое" << endl;
    cout << "3. Задание 1 - пары противоположных чисел" << endl;
    cout << "4. Задание 2 - обработка матрицы" << endl;
    cout << "5. Создать тестовый файл" << endl;
    cout << "0. Назад" << endl;
    cout << "Выбор: ";

    int choice;
    cin >> choice;

    if (choice == 0) break;

    switch (choice) {
      case 1: {
        int count, min_val, max_val;
        cout << "Количество чисел: ";
        cin >> count;
        cout << "Минимум: ";
        cin >> min_val;
        cout << "Максимум: ";
        cin >> max_val;
        BinaryProcessor::FillWithRandomNumbers(filename, count, min_val,
                                               max_val);
        break;
      }
      case 2:
        BinaryProcessor::DisplayNumbers(filename);
        break;
      case 3:
        BinaryProcessor::Task1CountOppositePairs(filename);
        break;
      case 4:
        BinaryProcessor::Task2MatrixProcessing(filename);
        break;
      case 5:
        BinaryProcessor::CreateTestNumbersFile(filename);
        break;
      default:
        cout << "Неверный выбор!" << endl;
    }
  }
}

void LuggageMenu() {
  string filename;
  cout << "Введите имя файла для данных о багаже: ";
  cin >> filename;

  while (true) {
    cout << "\n=== МЕНЮ БАГАЖА ===" << endl;
    cout << "1. Заполнить файл случайными данными" << endl;
    cout << "2. Показать содержимое файла" << endl;
    cout << "3. Задание 3 - разница масс" << endl;
    cout << "4. Создать тестовый файл" << endl;
    cout << "0. Назад" << endl;
    cout << "Выбор: ";

    int choice;
    cin >> choice;

    if (choice == 0) break;

    switch (choice) {
      case 1: {
        int passenger_count;
        cout << "Количество пассажиров: ";
        cin >> passenger_count;
        BinaryProcessor::FillWithRandomLuggage(filename, passenger_count);
        break;
      }
      case 2:
        BinaryProcessor::DisplayLuggage(filename);
        break;
      case 3:
        BinaryProcessor::Task3FindMassDifference(filename);
        break;
      case 4:
        BinaryProcessor::CreateTestLuggageFile(filename);
        break;
      default:
        cout << "Неверный выбор!" << endl;
    }
  }
}

void TextFileMenu() {
  string filename;
  cout << "Введите имя текстового файла (одно число в строке): ";
  cin >> filename;

  while (true) {
    cout << "\n=== МЕНЮ ТЕКСТОВЫХ ДАННЫХ (одно число в строке) ===" << endl;
    cout << "1. Заполнить файл случайными числами" << endl;
    cout << "2. Показать содержимое файла" << endl;
    cout << "3. Задание 4 - проверка отсутствия нуля" << endl;
    cout << "4. Создать тестовый файл" << endl;
    cout << "0. Назад" << endl;
    cout << "Выбор: ";

    int choice;
    cin >> choice;

    if (choice == 0) break;

    switch (choice) {
      case 1: {
        int count, min_val, max_val;
        cout << "Количество чисел: ";
        cin >> count;
        cout << "Минимум: ";
        cin >> min_val;
        cout << "Максимум: ";
        cin >> max_val;
        BinaryProcessor::FillTextFileWithRandomNumbers(filename, count, min_val,
                                                       max_val);
        break;
      }
      case 2:
        BinaryProcessor::DisplayTextFileContent(filename);
        break;
      case 3:
        BinaryProcessor::Task4CheckNoZero(filename);
        break;
      case 4:
        BinaryProcessor::CreateTestTextFile(filename);
        break;
      default:
        cout << "Неверный выбор!" << endl;
    }
  }
}

void TextFileMultipleMenu() {
  string filename;
  cout << "Введите имя текстового файла (несколько чисел в строке): ";
  cin >> filename;

  while (true) {
    cout << "\n=== МЕНЮ ТЕКСТОВЫХ ДАННЫХ (несколько чисел в строке) ==="
         << endl;
    cout << "1. Заполнить файл случайными числами" << endl;
    cout << "2. Показать содержимое файла" << endl;
    cout << "3. Задание 5 - найти максимальный элемент" << endl;
    cout << "4. Создать тестовый файл" << endl;
    cout << "0. Назад" << endl;
    cout << "Выбор: ";

    int choice;
    cin >> choice;

    if (choice == 0) break;

    switch (choice) {
      case 1: {
        int total_count, numbers_per_line, min_val, max_val;
        cout << "Общее количество чисел: ";
        cin >> total_count;
        cout << "Количество чисел в строке: ";
        cin >> numbers_per_line;
        cout << "Минимум: ";
        cin >> min_val;
        cout << "Максимум: ";
        cin >> max_val;
        BinaryProcessor::FillTextFileWithRandomNumbersMultiplePerLine(
            filename, total_count, numbers_per_line, min_val, max_val);
        break;
      }
      case 2:
        BinaryProcessor::DisplayTextFileContentMultiplePerLine(filename);
        break;
      case 3:
        BinaryProcessor::Task5FindMaxElement(filename);
        break;
      case 4:
        BinaryProcessor::CreateTestTextFileMultiplePerLine(filename);
        break;
      default:
        cout << "Неверный выбор!" << endl;
    }
  }
}

void TextFileStringsMenu() {
  string filename;
  cout << "Введите имя текстового файла (строки): ";
  cin >> filename;

  while (true) {
    cout << "\n=== МЕНЮ ТЕКСТОВЫХ ДАННЫХ (строки) ===" << endl;
    cout << "1. Заполнить файл случайными строками" << endl;
    cout << "2. Показать содержимое файла" << endl;
    cout << "3. Задание 6 - копировать строки, оканчивающиеся на символ"
         << endl;
    cout << "4. Создать тестовый файл" << endl;
    cout << "0. Назад" << endl;
    cout << "Выбор: ";

    int choice;
    cin >> choice;

    if (choice == 0) break;

    switch (choice) {
      case 1: {
        int line_count;
        cout << "Количество строк: ";
        cin >> line_count;
        BinaryProcessor::FillTextFileWithRandomStrings(filename, line_count);
        break;
      }
      case 2:
        BinaryProcessor::DisplayTextFileLines(filename);
        break;
      case 3: {
        string output_filename;
        char ending_char;
        cout << "Введите имя выходного файла: ";
        cin >> output_filename;
        cout << "Введите символ для фильтрации: ";
        cin >> ending_char;
        BinaryProcessor::Task6CopyLinesEndingWithChar(filename, output_filename,
                                                      ending_char);
        break;
      }
      case 4:
        BinaryProcessor::CreateTestTextFileWithStrings(filename);
        break;
      default:
        cout << "Неверный выбор!" << endl;
    }
  }
}

int main() {
  SetRussianLocale();

  cout << "ПРОГРАММА ДЛЯ РАБОТЫ С ФАЙЛАМИ" << endl;
  cout << "Задания 1-6 в одном классе со статическими методами" << endl;

  while (true) {
    ShowMenu();
    int choice;
    cin >> choice;

    if (choice == 0) break;

    switch (choice) {
      case 1:
        NumbersMenu();
        break;
      case 2:
        LuggageMenu();
        break;
      case 3:
        TextFileMenu();
        break;
      case 4:
        TextFileMultipleMenu();
        break;
      case 5:
        TextFileStringsMenu();
        break;
      default:
        cout << "Неверный выбор!" << endl;
    }
  }

  cout << "Выход из программы." << endl;
  return 0;
}