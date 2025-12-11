#include "binary_processor.h"

#include <Windows.h>

// Вспомогательные методы для добавления расширений
std::string BinaryProcessor::AddBinExtension(const std::string& filename) {
  std::string result = filename;
  if (result.find('.') == std::string::npos) {
    result += ".bin";
  }
  return result;
}

std::string BinaryProcessor::AddTxtExtension(const std::string& filename) {
  std::string result = filename;
  if (result.find('.') == std::string::npos) {
    result += ".txt";
  }
  return result;
}

// === Общие методы ===

void BinaryProcessor::DisplayBinaryContent(const std::string& filename) {
  std::string final_filename = AddBinExtension(filename);
  std::ifstream file(final_filename, std::ios::binary);
  if (!file) {
    std::cerr << "Файл '" << final_filename << "' не найден" << std::endl;
    return;
  }

  file.seekg(0, std::ios::end);
  size_t file_size = file.tellg();
  file.seekg(0, std::ios::beg);
}

// === Методы для заданий 1 и 2 ===

void BinaryProcessor::FillWithRandomNumbers(const std::string& filename,
                                            int count, int min_val,
                                            int max_val) {
  std::string final_filename = AddBinExtension(filename);
  std::ofstream file(final_filename, std::ios::binary);
  if (!file) {
    std::cerr << "Ошибка открытия файла: " << final_filename << std::endl;
    return;
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(min_val, max_val);

  for (int i = 0; i < count; ++i) {
    int number = dist(gen);
    file.write(reinterpret_cast<const char*>(&number), sizeof(number));
  }

  std::cout << "Бинарный файл '" << final_filename << "' заполнен " << count
            << " числами" << std::endl;
}

std::vector<int> BinaryProcessor::ReadNumbers(const std::string& filename) {
  std::vector<int> numbers;
  std::string final_filename = AddBinExtension(filename);
  std::ifstream file(final_filename, std::ios::binary);

  if (!file) {
    std::cerr << "Файл '" << final_filename << "' не найден" << std::endl;
    return numbers;
  }

  int number;
  while (file.read(reinterpret_cast<char*>(&number), sizeof(number))) {
    numbers.push_back(number);
  }

  return numbers;
}

void BinaryProcessor::DisplayNumbers(const std::string& filename) {
  std::vector<int> numbers = ReadNumbers(filename);
  if (numbers.empty()) {
    std::cout << "Файл пуст или не существует" << std::endl;
    return;
  }

  std::cout << "\nДесятичное содержимое файла '" << AddBinExtension(filename)
            << "':" << std::endl;
  for (size_t i = 0; i < numbers.size(); ++i) {
    std::cout << "[" << i << "] = " << numbers[i] << std::endl;
  }
  std::cout << "Всего элементов: " << numbers.size() << std::endl;
}

int BinaryProcessor::Task1CountOppositePairs(const std::string& filename) {
  std::vector<int> numbers = ReadNumbers(filename);
  if (numbers.empty()) return 0;

  int count = 0;
  std::cout << "\n=== ЗАДАНИЕ 1: Поиск пар противоположных чисел ==="
            << std::endl;

  for (size_t i = 0; i < numbers.size(); ++i) {
    for (size_t j = i + 1; j < numbers.size(); ++j) {
      if (numbers[i] != 0 && numbers[i] == -numbers[j]) {
        count++;
        std::cout << "Пара " << count << ": [" << i << "]=" << numbers[i]
                  << " и [" << j << "]=" << numbers[j] << std::endl;
      }
    }
  }

  std::cout << "Всего пар противоположных чисел: " << count << std::endl;
  return count;
}

int BinaryProcessor::FindMatrixSize(size_t element_count) {
  int n = 1;
  while (n * n < static_cast<int>(element_count)) n++;
  return n;
}

void BinaryProcessor::PrintMatrix(const std::vector<std::vector<int>>& matrix) {
  for (const auto& row : matrix) {
    for (int val : row) {
      std::cout << val << "\t";
    }
    std::cout << std::endl;
  }
}

void BinaryProcessor::Task2MatrixProcessing(const std::string& filename) {
  std::vector<int> numbers = ReadNumbers(filename);
  if (numbers.empty()) return;

  std::cout << "\n=== ЗАДАНИЕ 2: Обработка матрицы ===" << std::endl;

  int n = FindMatrixSize(numbers.size());
  std::cout << "Создание матрицы " << n << "x" << n << " из " << numbers.size()
            << " чисел" << std::endl;

  std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));
  size_t index = 0;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (index < numbers.size()) {
        matrix[i][j] = numbers[index++];
      }
    }
  }

  std::cout << "\nИсходная матрица:" << std::endl;
  PrintMatrix(matrix);

  std::vector<int> max_in_columns(n, INT_MIN);
  for (int j = 0; j < n; ++j) {
    for (int i = 0; i < n; ++i) {
      if (matrix[i][j] > max_in_columns[j]) {
        max_in_columns[j] = matrix[i][j];
      }
    }
    std::cout << "Столбец " << j << ": максимум = " << max_in_columns[j]
              << std::endl;
  }

  std::vector<std::vector<int>> result_matrix(n, std::vector<int>(n));
  for (int j = 0; j < n; ++j) {
    for (int i = 0; i < n; ++i) {
      result_matrix[i][j] = max_in_columns[j];
    }
  }

  std::cout << "\nМатрица после замены столбцов на максимальные элементы:"
            << std::endl;
  PrintMatrix(result_matrix);
}

// === Методы для задания 3 ===

void BinaryProcessor::FillWithRandomLuggage(const std::string& filename,
                                            int passenger_count) {
  std::string final_filename = AddBinExtension(filename);
  std::ofstream file(final_filename, std::ios::binary);
  if (!file) {
    std::cerr << "Ошибка открытия файла: " << final_filename << std::endl;
    return;
  }

  std::vector<std::string> luggage_types = {
      "чемодан", "сумка",      "коробка",          "рюкзак",  "портфель",
      "кофр",    "чемоданчик", "сумка спортивная", "корзина", "кейс"};

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> weight_dist(1.0, 30.0);
  std::uniform_int_distribution<int> type_dist(
      0, static_cast<int>(luggage_types.size()) - 1);
  std::uniform_int_distribution<int> items_count_dist(1, 5);

  int total_items = 0;

  for (int i = 0; i < passenger_count; ++i) {
    int items_count = items_count_dist(gen);

    for (int j = 0; j < items_count; ++j) {
      Luggage luggage;
      std::string item_name = luggage_types[type_dist(gen)];
      strncpy_s(luggage.item_name, item_name.c_str(), 49);
      luggage.item_name[49] = '\0';
      luggage.weight = weight_dist(gen);

      file.write(reinterpret_cast<const char*>(&luggage), sizeof(Luggage));
      total_items++;
    }
  }

  std::cout << "Файл '" << final_filename << "' заполнен. " << passenger_count
            << " пассажиров, " << total_items << " единиц багажа" << std::endl;
}

std::vector<Luggage> BinaryProcessor::ReadLuggage(const std::string& filename) {
  std::vector<Luggage> luggage_list;
  std::string final_filename = AddBinExtension(filename);
  std::ifstream file(final_filename, std::ios::binary);

  if (!file) {
    std::cerr << "Файл '" << final_filename << "' не найден" << std::endl;
    return luggage_list;
  }

  Luggage item;
  while (file.read(reinterpret_cast<char*>(&item), sizeof(Luggage))) {
    luggage_list.push_back(item);
  }

  return luggage_list;
}

void BinaryProcessor::DisplayLuggage(const std::string& filename) {
  std::vector<Luggage> luggage_list = ReadLuggage(filename);
  if (luggage_list.empty()) {
    std::cout << "Файл пуст или не существует" << std::endl;
    return;
  }

  std::cout << "\nСодержимое файла '" << AddBinExtension(filename)
            << "':" << std::endl;
  std::cout << "==============================================" << std::endl;
  std::cout << std::left << std::setw(5) << "№" << std::setw(25) << "Вид багажа"
            << "Вес (кг)" << std::endl;
  std::cout << "----------------------------------------------" << std::endl;

  double total_weight = 0;
  for (size_t i = 0; i < luggage_list.size(); ++i) {
    std::cout << std::left << std::setw(5) << i + 1 << std::setw(25)
              << luggage_list[i].item_name << std::fixed << std::setprecision(2)
              << luggage_list[i].weight << std::endl;
    total_weight += luggage_list[i].weight;
  }

  std::cout << "----------------------------------------------" << std::endl;
  std::cout << "Всего единиц багажа: " << luggage_list.size() << std::endl;
  std::cout << "Общий вес: " << total_weight << " кг" << std::endl;
}

double BinaryProcessor::Task3FindMassDifference(const std::string& filename) {
  std::vector<Luggage> luggage_list = ReadLuggage(filename);
  if (luggage_list.empty()) {
    std::cout << "Файл пуст, невозможно выполнить задание" << std::endl;
    return 0.0;
  }

  auto max_element = std::max_element(
      luggage_list.begin(), luggage_list.end(),
      [](const Luggage& a, const Luggage& b) { return a.weight < b.weight; });

  auto min_element = std::min_element(
      luggage_list.begin(), luggage_list.end(),
      [](const Luggage& a, const Luggage& b) { return a.weight < b.weight; });

  double max_weight = max_element->weight;
  double min_weight = min_element->weight;
  double difference = max_weight - min_weight;

  std::cout << "\n=== ЗАДАНИЕ 3: Разница масс багажа ===" << std::endl;
  std::cout << "Багаж максимальной массы: '" << max_element->item_name << "' - "
            << max_weight << " кг" << std::endl;
  std::cout << "Багаж минимальной массы: '" << min_element->item_name << "' - "
            << min_weight << " кг" << std::endl;
  std::cout << "Разница: " << difference << " кг" << std::endl;

  return difference;
}

// === Методы для задания 4 (текстовый файл) ===

void BinaryProcessor::FillTextFileWithRandomNumbers(const std::string& filename,
                                                    int count, int min_val,
                                                    int max_val) {
  std::string final_filename = AddTxtExtension(filename);
  std::ofstream file(final_filename);
  if (!file) {
    std::cerr << "Ошибка открытия текстового файла: " << final_filename
              << std::endl;
    return;
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(min_val, max_val);

  for (int i = 0; i < count; ++i) {
    file << dist(gen) << std::endl;
  }

  std::cout << "Текстовый файл '" << final_filename << "' заполнен " << count
            << " числами" << std::endl;
}

std::vector<int> BinaryProcessor::ReadNumbersFromTextFile(
    const std::string& filename) {
  std::vector<int> numbers;
  std::string final_filename = AddTxtExtension(filename);
  std::ifstream file(final_filename);

  if (!file) {
    std::cerr << "Текстовый файл '" << final_filename << "' не найден"
              << std::endl;
    return numbers;
  }

  std::string line;
  while (std::getline(file, line)) {
    if (!line.empty()) {
      try {
        numbers.push_back(std::stoi(line));
      } catch (const std::exception& e) {
        std::cerr << "Ошибка преобразования строки в число: " << line
                  << std::endl;
      }
    }
  }

  return numbers;
}

void BinaryProcessor::DisplayTextFileContent(const std::string& filename) {
  std::vector<int> numbers = ReadNumbersFromTextFile(filename);
  if (numbers.empty()) {
    std::cout << "Текстовый файл пуст или не существует" << std::endl;
    return;
  }

  std::cout << "\nСодержимое текстового файла '" << AddTxtExtension(filename)
            << "':" << std::endl;
  for (size_t i = 0; i < numbers.size(); ++i) {
    std::cout << "Строка " << i + 1 << ": " << numbers[i] << std::endl;
  }
  std::cout << "Всего чисел: " << numbers.size() << std::endl;
}

bool BinaryProcessor::Task4CheckNoZero(const std::string& filename) {
  std::vector<int> numbers = ReadNumbersFromTextFile(filename);
  if (numbers.empty()) {
    std::cout << "Файл пуст, считаем что не содержит нуля" << std::endl;
    return true;
  }

  std::cout << "\n=== ЗАДАНИЕ 4: Проверка отсутствия нуля ===" << std::endl;

  bool has_zero = false;
  std::vector<size_t> zero_positions;

  for (size_t i = 0; i < numbers.size(); ++i) {
    if (numbers[i] == 0) {
      has_zero = true;
      zero_positions.push_back(i + 1);
    }
  }

  if (has_zero) {
    std::cout << "Файл СОДЕРЖИТ нулевые значения!" << std::endl;
    std::cout << "Нули найдены в строках: ";
    for (size_t i = 0; i < zero_positions.size(); ++i) {
      std::cout << zero_positions[i];
      if (i < zero_positions.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
    return false;
  } else {
    std::cout << "Файл НЕ СОДЕРЖИТ нулевых значений" << std::endl;
    return true;
  }
}

// === Методы для задания 5 (текстовый файл - несколько чисел в строке) ===

void BinaryProcessor::FillTextFileWithRandomNumbersMultiplePerLine(
    const std::string& filename, int total_count, int numbers_per_line,
    int min_val, int max_val) {
  std::string final_filename = AddTxtExtension(filename);
  std::ofstream file(final_filename);
  if (!file) {
    std::cerr << "Ошибка открытия текстового файла: " << final_filename
              << std::endl;
    return;
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(min_val, max_val);

  int numbers_written = 0;

  while (numbers_written < total_count) {
    int numbers_in_this_line =
        std::min<size_t>(numbers_per_line, total_count - numbers_written);

    for (int i = 0; i < numbers_in_this_line; ++i) {
      file << dist(gen);
      if (i < numbers_in_this_line - 1) {
        file << " ";
      }
      numbers_written++;
    }
    file << std::endl;
  }

  std::cout << "Текстовый файл '" << final_filename << "' заполнен "
            << total_count << " числами (" << numbers_per_line
            << " чисел в строке)" << std::endl;
}

std::vector<int> BinaryProcessor::ReadNumbersFromTextFileMultiplePerLine(
    const std::string& filename) {
  std::vector<int> numbers;
  std::string final_filename = AddTxtExtension(filename);
  std::ifstream file(final_filename);

  if (!file) {
    std::cerr << "Текстовый файл '" << final_filename << "' не найден"
              << std::endl;
    return numbers;
  }

  std::string line;
  int line_number = 1;

  while (std::getline(file, line)) {
    if (!line.empty()) {
      std::stringstream ss(line);
      std::string token;

      while (std::getline(ss, token, ' ')) {
        if (!token.empty()) {
          try {
            numbers.push_back(std::stoi(token));
          } catch (const std::exception& e) {
            std::cerr << "Ошибка преобразования в строке " << line_number
                      << ": '" << token << "'" << std::endl;
          }
        }
      }
    }
    line_number++;
  }

  return numbers;
}

void BinaryProcessor::DisplayTextFileContentMultiplePerLine(
    const std::string& filename) {
  std::string final_filename = AddTxtExtension(filename);
  std::ifstream file(final_filename);
  if (!file) {
    std::cout << "Текстовый файл пуст или не существует" << std::endl;
    return;
  }

  std::cout << "\nСодержимое текстового файла '" << final_filename
            << "':" << std::endl;
  std::cout << "==============================================" << std::endl;

  std::string line;
  int line_number = 1;
  std::vector<int> all_numbers;

  while (std::getline(file, line)) {
    if (!line.empty()) {
      std::cout << "Строка " << line_number << ": " << line << std::endl;

      std::stringstream ss(line);
      std::string token;
      while (std::getline(ss, token, ' ')) {
        if (!token.empty()) {
          try {
            all_numbers.push_back(std::stoi(token));
          } catch (const std::exception& e) {
            // Игнорируем ошибки преобразования при выводе
          }
        }
      }
    }
    line_number++;
  }

  std::cout << "==============================================" << std::endl;
  std::cout << "Всего строк: " << (line_number - 1) << std::endl;
  std::cout << "Всего чисел: " << all_numbers.size() << std::endl;
}

int BinaryProcessor::Task5FindMaxElement(const std::string& filename) {
  std::vector<int> numbers = ReadNumbersFromTextFileMultiplePerLine(filename);
  if (numbers.empty()) {
    std::cout << "Файл пуст, невозможно найти максимальный элемент"
              << std::endl;
    return 0;
  }

  std::cout << "\n=== ЗАДАНИЕ 5: Поиск максимального элемента ===" << std::endl;

  int max_element = numbers[0];
  for (size_t i = 1; i < numbers.size(); ++i) {
    if (numbers[i] > max_element) {
      max_element = numbers[i];
    }
  }

  std::cout << "Количество чисел в файле: " << numbers.size() << std::endl;
  std::cout << "Минимальный элемент: "
            << *std::min_element(numbers.begin(), numbers.end()) << std::endl;
  std::cout << "Максимальный элемент: " << max_element << std::endl;

  std::cout << "Максимальный элемент встречается в позициях: ";
  bool first = true;
  for (size_t i = 0; i < numbers.size(); ++i) {
    if (numbers[i] == max_element) {
      if (!first) std::cout << ", ";
      std::cout << i + 1;
      first = false;
    }
  }
  std::cout << std::endl;

  return max_element;
}

// === Методы для задания 6 (текстовый файл - работа со строками) ===

void BinaryProcessor::FillTextFileWithRandomStrings(const std::string& filename,
                                                    int line_count) {
  std::string final_filename = AddTxtExtension(filename);
  std::ofstream file(final_filename);
  if (!file) {
    std::cerr << "Ошибка открытия текстового файла: " << final_filename
              << std::endl;
    return;
  }

  std::vector<std::string> sample_words = {
      "дом",       "кот",       "стол",     "окно",   "книга",
      "ручка",     "солнце",    "ветер",    "дождь",  "снег",
      "город",     "улица",     "машина",   "цветок", "музыка",
      "компьютер", "программа", "алгоритм", "данные", "файл"};

  std::vector<std::string> endings = {".", "!", "?", ",", ";"};

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> word_dist(0, sample_words.size() - 1);
  std::uniform_int_distribution<int> length_dist(1, 5);
  std::uniform_int_distribution<int> end_dist(0, endings.size() - 1);

  for (int i = 0; i < line_count; ++i) {
    int words_in_line = length_dist(gen);
    std::string line;

    for (int j = 0; j < words_in_line; ++j) {
      line += sample_words[word_dist(gen)];
      if (j < words_in_line - 1) {
        line += " ";
      }
    }

    line += endings[end_dist(gen)];
    file << line << std::endl;
  }

  std::cout << "Текстовый файл '" << final_filename << "' заполнен "
            << line_count << " строками" << std::endl;
}

void BinaryProcessor::DisplayTextFileLines(const std::string& filename) {
  std::string final_filename = AddTxtExtension(filename);
  std::ifstream file(final_filename);
  if (!file) {
    std::cout << "Текстовый файл пуст или не существует" << std::endl;
    return;
  }

  std::cout << "\nСодержимое текстового файла '" << final_filename
            << "':" << std::endl;
  std::cout << "==============================================" << std::endl;

  std::string line;
  int line_number = 1;

  while (std::getline(file, line)) {
    if (!line.empty()) {
      std::cout << "Строка " << line_number << ": '" << line << "'";
      if (!line.empty()) {
        std::cout << " (последний символ: '" << line.back() << "')";
      }
      std::cout << std::endl;
      line_number++;
    }
  }

  std::cout << "==============================================" << std::endl;
  std::cout << "Всего строк: " << (line_number - 1) << std::endl;
}

void BinaryProcessor::Task6CopyLinesEndingWithChar(
    const std::string& input_filename, const std::string& output_filename,
    char ending_char) {
  std::string final_input_filename = AddTxtExtension(input_filename);
  std::string final_output_filename = AddTxtExtension(output_filename);

  std::ifstream input_file(final_input_filename);
  std::ofstream output_file(final_output_filename);

  if (!input_file) {
    std::cerr << "Ошибка открытия входного файла: " << final_input_filename
              << std::endl;
    return;
  }

  if (!output_file) {
    std::cerr << "Ошибка открытия выходного файла: " << final_output_filename
              << std::endl;
    return;
  }

  std::string line;
  int total_lines = 0;
  int copied_lines = 0;

  std::cout << "\n=== ЗАДАНИЕ 6: Копирование строк, оканчивающихся на символ '"
            << ending_char << "' ===" << std::endl;

  while (std::getline(input_file, line)) {
    total_lines++;
    if (!line.empty() && line.back() == ending_char) {
      output_file << line << std::endl;
      copied_lines++;
      std::cout << "Скопирована строка " << total_lines << ": '" << line << "'"
                << std::endl;
    }
  }

  std::cout << "==============================================" << std::endl;
  std::cout << "Обработано строк: " << total_lines << std::endl;
  std::cout << "Скопировано строк: " << copied_lines << std::endl;
  std::cout << "Результат записан в файл: " << final_output_filename
            << std::endl;

  input_file.close();
  output_file.close();
}

// === Вспомогательные методы ===

void BinaryProcessor::CreateTestNumbersFile(const std::string& filename) {
  std::string final_filename = AddBinExtension(filename);
  std::ofstream file(final_filename, std::ios::binary);
  int test_numbers[] = {5, -5, 10, -10, 3, 7, -3, 8, 15, -15, 2, 4, 6, 9, 11};

  for (int num : test_numbers) {
    file.write(reinterpret_cast<const char*>(&num), sizeof(num));
  }

  std::cout << "Создан тестовый бинарный файл '" << final_filename
            << "' с числами: ";
  for (int num : test_numbers) std::cout << num << " ";
  std::cout << std::endl;
}

void BinaryProcessor::CreateTestLuggageFile(const std::string& filename) {
  std::string final_filename = AddBinExtension(filename);
  std::ofstream file(final_filename, std::ios::binary);

  std::vector<Luggage> test_luggage = {
      Luggage("чемодан", 15.5),    Luggage("сумка", 8.2),
      Luggage("коробка", 25.7),    Luggage("рюкзак", 12.1),
      Luggage("портфель", 5.8),    Luggage("кофр", 18.3),
      Luggage("чемоданчик", 10.0), Luggage("сумка спортивная", 6.5),
      Luggage("корзина", 30.2),    Luggage("кейс", 3.7)};

  for (const auto& item : test_luggage) {
    file.write(reinterpret_cast<const char*>(&item), sizeof(Luggage));
  }

  std::cout << "Создан тестовый файл '" << final_filename
            << "' с 10 единицами багажа" << std::endl;
}

void BinaryProcessor::CreateTestTextFile(const std::string& filename) {
  std::string final_filename = AddTxtExtension(filename);
  std::ofstream file(final_filename);

  int with_zero[] = {5, -3, 10, 0, 7, 2, 8, -1, 4, 6};
  int without_zero[] = {5, -3, 10, 7, 2, 8, -1, 4, 6, 9};

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(0, 1);

  if (dist(gen) == 0) {
    for (int num : with_zero) {
      file << num << std::endl;
    }
    std::cout << "Создан тестовый текстовый файл '" << final_filename
              << "' С нулем: ";
    for (int num : with_zero) std::cout << num << " ";
    std::cout << std::endl;
  } else {
    for (int num : without_zero) {
      file << num << std::endl;
    }
    std::cout << "Создан тестовый текстовый файл '" << final_filename
              << "' БЕЗ нуля: ";
    for (int num : without_zero) std::cout << num << " ";
    std::cout << std::endl;
  }
}

void BinaryProcessor::CreateTestTextFileMultiplePerLine(
    const std::string& filename) {
  std::string final_filename = AddTxtExtension(filename);
  std::ofstream file(final_filename);

  std::vector<std::vector<int>> test_data = {{15, -3, 42, 7},
                                             {8, 0, -15, 23},
                                             {100, -50, 33, 17},
                                             {5, 88, -7, 42},
                                             {19, 21, 100, 4}};

  for (const auto& line : test_data) {
    for (size_t i = 0; i < line.size(); ++i) {
      file << line[i];
      if (i < line.size() - 1) {
        file << " ";
      }
    }
    file << std::endl;
  }

  std::cout << "Создан тестовый текстовый файл '" << final_filename
            << "' с несколькими числами в строке" << std::endl;
}

void BinaryProcessor::CreateTestTextFileWithStrings(
    const std::string& filename) {
  std::string final_filename = AddTxtExtension(filename);
  std::ofstream file(final_filename);

  std::vector<std::string> test_lines = {"Привет мир.",
                                         "Как дела?",
                                         "Сегодня хорошая погода!",
                                         "Программирование это интересно.",
                                         "C++ мощный язык.",
                                         "Что нового?",
                                         "Отличная работа!",
                                         "Продолжаем учиться.",
                                         "Вопросы и ответы?",
                                         "Конец задания."};

  for (const auto& line : test_lines) {
    file << line << std::endl;
  }

  std::cout << "Создан тестовый текстовый файл '" << final_filename
            << "' со строками:" << std::endl;
  for (const auto& line : test_lines) {
    std::cout << "  '" << line << "'" << std::endl;
  }
}