#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
using namespace std;

// Забороняється змінювати сигнатуру функцій Task1 і Task2!
// Дозволяється створювати довільну кількість допоміжних функцій

// Завдання 1
//
// Функція приймає у якості аргументів:
// * рядок адреси (назви) файлу, який містить дані про матрицю, яка множиться
//   на вектор (дані подані у вигляді чисел, розділених пробілами та переходами
//   на новий рядок);
// * рядок адреси (назви) файлу, який містить дані про вектор, на який
//   множиться матриця (дані подані у вигляді чисел, розділених пробілами та
//   переходами на новий рядок);
// * ціле число procNum, яке вказує на те, скільки обчислювачів, між якими слід
//   розподілити обчислювальне навантаження, доступно у системі (кількість
//   потоків);
// * ціле число rowNum, яке вказує кількість рядків матриці, яка множиться на
//   вектор;
// * ціле число colNum, яке вказує кількість стовпців матриці, яка множиться на
//   вектор.
//
// У випадку коректного відкривання і зчитування файлів та коректних значень
// procNum, rowNum, colNum, функція повинна повертати рядок, який міститиме
// результат (значення вектор-стовпця результату) паралельного множення заданої
// матриці на заданий вектор, яке виконане методом смугового розбиття матриці
// по рядках. Наприклад:
// Task1("testfiles/matrix1_rows.txt", "testfiles/vector1_rows.txt", 4, 8, 10) - "-1563\n12589\n15693\n58071\n24369\n-93975\n94960\n-33994\n" (без лапок)
//
// У випадку відсутності файлу з матрицею або неможливості відкрити його для
// роботи функція має повертати вивід:
// "No file containing matrix or file is corrupted" (без лапок).
//
// У випадку відсутності файлу з вектором або неможливості відкрити його для
// роботи функція має повертати вивід:
// "No file containing vector or file is corrupted" (без лапок).
//
// У випадку некоректного значення кількості обчислювачів або кількості рядків
// чи стовпців матриці, функція має повертати вивід:
// "Error" (без лапок).
//
// У випадку, якщо кількість рядків не є кратною кількості обчислювачів,
// функція має повертати вивід
// "Number of rows is not a multiple of processing unit number" (без лапок).

vector<vector<int>> readMatrixFromFile(const string &fileName, int rowNum, int colNum)
{
    ifstream file(fileName);
    vector<vector<int>> matrix(rowNum, vector<int>(colNum, 0));

    for (int i = 0; i < rowNum; ++i)
        for (int j = 0; j < colNum; ++j)
            file >> matrix[i][j];

    file.close();
    return matrix;
}

vector<int> readVectorFromFile(const string &fileName, int size)
{
    ifstream file(fileName);
    vector<int> vectorData(size, 0);

    for (int i = 0; i < size; ++i)
        file >> vectorData[i];

    file.close();
    return vectorData;
}

vector<int> parallelMatrixVectorMultiply(const vector<vector<int>> &matrix, const vector<int> &vectorData, int procNum)
{
    int rowNum = matrix.size();
    int colNum = matrix[0].size();
    vector<int> result(rowNum, 0);
    vector<thread> threads;

    auto multiplyPart = [&](int start, int end)
    {
        for (int i = start; i < end; ++i)
            for (int j = 0; j < colNum; ++j)
                result[i] += matrix[i][j] * vectorData[j];
    };

    int rowsPerThread = rowNum / procNum;

    for (int i = 0; i < procNum; ++i)
    {
        int start = i * rowsPerThread;
        int end = (i == procNum - 1) ? rowNum : (i + 1) * rowsPerThread;
        threads.emplace_back(multiplyPart, start, end);
    }

    for (auto &thread : threads)
        thread.join();

    return result;
}

string Task1(string matrixFile, string vectorFile, int procNum, int rowNum, int colNum)
{
    ifstream file(matrixFile);
    if (!file.is_open())
        return "No file containing matrix or file is corrupted";
    file.close();

    file.open(vectorFile);
    if (!file.is_open())
        return "No file containing vector or file is corrupted";
    file.close();

    if (procNum <= 0 || rowNum <= 0 || colNum <= 0)
        return "Error";

    if (rowNum % procNum != 0)
        return "Number of rows is not a multiple of processing unit number";

    // Об'єктом stringstream можна користуватись як і об'єктом iostream
    // Наприклад, коректним є запис
    // functionOutput << arr[i] << " ";
    stringstream functionOutput;

    // Розмістіть тут Ваш код

    vector<int> result = parallelMatrixVectorMultiply(
        readMatrixFromFile(matrixFile, rowNum, colNum),
        readVectorFromFile(vectorFile, colNum), procNum);

    for (int i : result)
        functionOutput << i << "\n";

    // Конвертування об'єкту stringstream у рядок для відповідності сигнатурі функції
    return functionOutput.str();
}

// Завдання 2
//
// Функція приймає у якості аргументів:
// * рядок адреси (назви) файлу, який містить дані про матрицю, яка множиться
//   на вектор (дані подані у вигляді чисел, розділених пробілами та переходами
//   на новий рядок);
// * рядок адреси (назви) файлу, який містить дані про вектор, на який
//   множиться матриця (дані подані у вигляді чисел, розділених пробілами та
//   переходами на новий рядок);
// * ціле число procNum, яке вказує на те, скільки обчислювачів, між якими слід
//   розподілити обчислювальне навантаження, доступно у системі (кількість
//   потоків);
// * ціле число rowNum, яке вказує кількість рядків матриці, яка множиться на
//   вектор;
// * ціле число colNum, яке вказує кількість стовпців матриці, яка множиться на
//   вектор.
//
// У випадку коректного відкривання і зчитування файлів та коректних значень
// procNum, rowNum, colNum, функція повинна повертати рядок, який міститиме
// результат (значення вектор-стовпця результату) паралельного множення заданої
// матриці на заданий вектор, яке виконане методом смугового розбиття матриці
// по стовпцях. Наприклад:
// Task1("testfiles/matrix1_rows.txt", "testfiles/vector1_rows.txt", 4, 8, 10) - "-1563\n12589\n15693\n58071\n24369\n-93975\n94960\n-33994\n" (без лапок)
//
// У випадку відсутності файлу з матрицею або неможливості відкрити його для
// роботи функція має повертати вивід:
// "No file containing matrix or file is corrupted" (без лапок).
//
// У випадку відсутності файлу з вектором або неможливості відкрити його для
// роботи функція має повертати вивід:
// "No file containing vector or file is corrupted" (без лапок).
//
// У випадку некоректного значення кількості обчислювачів або кількості рядків
// чи стовпців матриці, функція має повертати вивід:
// "Error" (без лапок).
//
// У випадку, якщо кількість стовпців не є кратною кількості обчислювачів,
// функція має повертати вивід
// "Number of columns is not a multiple of processing unit number" (без лапок).
string Task2(string matrixFile, string vectorFile, int procNum, int rowNum, int colNum)
{
    ifstream file(matrixFile);
    if (!file.is_open())
        return "No file containing matrix or file is corrupted";
    file.close();

    file.open(vectorFile);
    if (!file.is_open())
        return "No file containing vector or file is corrupted";
    file.close();

    if (procNum <= 0 || rowNum <= 0 || colNum <= 0)
        return "Error";

    if (colNum % procNum != 0)
        return "Number of columns is not a multiple of processing unit number";

    // Об'єктом stringstream можна користуватись як і об'єктом iostream
    // Наприклад, коректним є запис
    // functionOutput << arr[i] << " ";
    stringstream functionOutput;

    // Розмістіть тут Ваш код
    vector<int> result = parallelMatrixVectorMultiply(
        readMatrixFromFile(matrixFile, rowNum, colNum),
        readVectorFromFile(vectorFile, colNum), procNum);

    for (int i : result)
        functionOutput << i << "\n";

    // Конвертування об'єкту stringstream у рядок для відповідності сигнатурі функції
    return functionOutput.str();
}
