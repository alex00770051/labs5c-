#ifndef LABS_BINARY_PROCESSOR_H_
#define LABS_BINARY_PROCESSOR_H_

#include <algorithm>
#include <bitset>
#include <climits>
#include <codecvt>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale>
#include <random>
#include <sstream>
#include <string>
#include <vector>

// Структура для задания 3
struct Luggage {
  char item_name[50];  // название единицы багажа
  double weight;       // масса в кг

  Luggage(const char* name = "", double w = 0.0) {
    strncpy_s(item_name, name, 49);
    item_name[49] = '\0';
    weight = w;
  }
};

class BinaryProcessor {
 public:
  // === Общие методы ===
  static void DisplayBinaryContent(const std::string& filename);

  // === Методы для заданий 1 и 2 (числовые данные) ===
  static void FillWithRandomNumbers(const std::string& filename, int count,
                                    int min_val = -100, int max_val = 100);
  static std::vector<int> ReadNumbers(const std::string& filename);
  static void DisplayNumbers(const std::string& filename);

  // Задание 1
  static int Task1CountOppositePairs(const std::string& filename);

  // Задание 2
  static void Task2MatrixProcessing(const std::string& filename);

  // === Методы для задания 3 (структуры) ===
  static void FillWithRandomLuggage(const std::string& filename,
                                    int passenger_count);
  static std::vector<Luggage> ReadLuggage(const std::string& filename);
  static void DisplayLuggage(const std::string& filename);

  // Задание 3
  static double Task3FindMassDifference(const std::string& filename);

  // === Методы для задания 4 (текстовый файл - по одному числу в строке) ===
  static void FillTextFileWithRandomNumbers(const std::string& filename,
                                            int count, int min_val = -100,
                                            int max_val = 100);
  static std::vector<int> ReadNumbersFromTextFile(const std::string& filename);
  static void DisplayTextFileContent(const std::string& filename);
  static bool Task4CheckNoZero(const std::string& filename);

  // === Методы для задания 5 (текстовый файл - несколько чисел в строке) ===
  static void FillTextFileWithRandomNumbersMultiplePerLine(
      const std::string& filename, int total_count, int numbers_per_line,
      int min_val = -100, int max_val = 100);
  static std::vector<int> ReadNumbersFromTextFileMultiplePerLine(
      const std::string& filename);
  static void DisplayTextFileContentMultiplePerLine(
      const std::string& filename);
  static int Task5FindMaxElement(const std::string& filename);

  // === Методы для задания 6 (текстовый файл - работа со строками) ===
  static void FillTextFileWithRandomStrings(const std::string& filename,
                                            int line_count);
  static void DisplayTextFileLines(const std::string& filename);
  static void Task6CopyLinesEndingWithChar(const std::string& input_filename,
                                           const std::string& output_filename,
                                           char ending_char);

  // === Вспомогательные методы ===
  static void CreateTestNumbersFile(const std::string& filename);
  static void CreateTestLuggageFile(const std::string& filename);
  static void CreateTestTextFile(const std::string& filename);
  static void CreateTestTextFileMultiplePerLine(const std::string& filename);
  static void CreateTestTextFileWithStrings(const std::string& filename);

 private:
  static int FindMatrixSize(size_t element_count);
  static void PrintMatrix(const std::vector<std::vector<int>>& matrix);

  // Вспомогательные методы для добавления расширений
  static std::string AddBinExtension(const std::string& filename);
  static std::string AddTxtExtension(const std::string& filename);

  BinaryProcessor() = delete;  // Запрет создания экземпляров
  BinaryProcessor(const BinaryProcessor&) = delete;
  BinaryProcessor& operator=(const BinaryProcessor&) = delete;
};

#endif  