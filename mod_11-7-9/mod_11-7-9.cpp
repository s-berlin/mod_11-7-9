// Сортировка большого массива
#include <string>
#include <fstream>  // работа с файлами
#include <iostream>
#include <cstdlib> // для получения рандомных чисел
#include <ctime>
#include <chrono>
#include <stdio.h>

using namespace std;

struct bucket {
    int count; // количество элементов в корзине
    int* data; // массив элементов корзины
};

void write_arr(const string& filename, const int* arr, const int n)
{
    fstream fs;

    fs.open(filename, fstream::out);
    if (fs.is_open()) // проверяем, что файл успешно открыт
    {
        fs << n << '\n';  // записываем размер массива
        for (int i = 0; i < n; i++)
            fs << arr[i] << ' '; // записываем значения через пробел
        fs << '\n';

        fs.close(); // закрываем файл
    }
}

void read_arr(const string& filename, int*& arr, int& n)
{
    fstream fs;

    fs.open(filename, fstream::in);
    if (fs.is_open()) // проверяем, что файл успешно открыт
    {
        fs >> n;  // читаем размер массива
        arr = new int[n];
        for (int i = 0; i < n; i++)
            fs >> arr[i]; // читаем из файла разделительные символы - пробел и перенос строки

        fs.close(); // закрываем файл
    }
}

void swap(int* a, int* b) // функция для смены местами двух значений
{
    int temp = *a;
    *a = *b;
    *b = temp;
}



//=============================================================================================================
int getMax(int* arr, int n) // функция находжения максимального элемента массива
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}
//------------------------------------------------------------------------------------------------------------
int getExp(int value) {
    int exp = 1;

    while (value > 10)
    {
        value /= 10;
        exp *= 10;
    }

    return exp;
}
//------------------------------------------------------------------------------------------------------------
void countSort(int* arr, int n)
{
    if (!n)
        return;

    int* output = new int[n];
    int max = getMax(arr, n);
    int* count = new int[max + 1];

    for (int i = 0; i < max + 1; i++)
        count[i] = 0;

    for (int i = 0; i < n; i++)
        count[arr[i]]++;  // подсчитываем  частоту повторения элементов

    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];  // вычисляем накопленные суммы

    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];  // устанавливаем элемент на корректное место 
        count[arr[i]]--; // уменьшаем частоту, так как уже записали элемент
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];

    delete[] output;
    delete[] count;
}

//=============================================================================================================
// формирование исходного файла: 39 раз добавляем по 10 млн элементов
// сортировка: 1) читаем 30 млн элементов в массив, сортируем, записываем в файл array_data_s
//             2) в цикле читаем очередные 30 млн элементов в массив, сортируем, 
//                объединяем с файлом array_data_s в файл array_data_s1, 
//                переименовываем array_data_s1 в array_data_s
int main()
{
    string filename = "array_data_2_Gb.txt";   // исходный файл
    string filename_s = "array_data_s.txt";   // конечный отсортированный файл
    string filename_s1 = "array_data_s1.txt"; // файл, объединяющий очередной отсортированный массив с конечным отсортированным файлом
    string filename_s2 = "array_data_s2.txt"; // файл, объединяющий очередной отсортированный массив с конечным отсортированным файлом
    string filename_sn[8] = { "s1.txt","s2.txt","s3.txt","s4.txt","s5.txt","s6.txt","s7.txt","s8.txt" }; // промежуточные отсортированные файлы по 50 млн
    string filename_sn2[4] = { "s12.txt","s34.txt","s56.txt","s78.txt" }; // промежуточные отсортированные файлы по 100 млн
    string filename_sn3[2] = { "s1234.txt","s5678.txt" }; // промежуточные отсортированные файлы по 200 млн

    fstream fi;
    fstream fs;
    fstream fs1;
    fstream fs2;
    int numb, numb2;                                 // элемент файла


    int k = 40;  // кол-во циклов по 10 млн при формировании исходного массива 2Гб

    setlocale(LC_ALL, "");

    //-------------------------------------------------------------------------------------------------------------------------
    const int size = 10000000;
    int fi_exist = 0; // признак наличия исходного файла (1 - есть, 0 - нет)
    if (fi_exist == 0) {

        auto start1 = chrono::high_resolution_clock::now(); // сохраняем время начала формирования исходного файла

        fi.open(filename, fstream::out);

        int* rand_arr = new int[size];
        // записываем в файл 40 раз по 10 млн элементов
        cout << "Записываем в исходный файл " << k << " раз по " << size << " элементов" << endl;
        for (int j = 0; j < k; j++) {
            cout << j + 1 << endl;
            srand(time(nullptr)); // используем текущее время, чтобы сгенерировать рандомные значения
            int lef_border = 1;
            int range_len = 30000 + 50 * j + 1; // правая граница = range_len + left_border      30000 + 50 * j + 1
                                                // range_len в цикле меняется, чтобы следующий блок элементов хоть немного отличался от предыдущих
            for (int i = 0; i < size; i++) {
                rand_arr[i] = lef_border + rand() % range_len; // генерируем число в указанном диапазоне и записываем в массив
                fi << rand_arr[i] << ' '; // записываем значения через пробел
            }

            fi << '\n';
        }
        cout << "Сформирован исходный файл array_data_2_Gb.txt" << endl;
        fi.close(); // закрываем файл
        delete[] rand_arr;

        auto finish1 = chrono::high_resolution_clock::now(); // сохраняем время конца формирования исходного файла
        chrono::duration<double> elapsed1 = finish1 - start1;
        cout << "Время формирования исходного файла: " << elapsed1.count() << " sec" << endl << endl; // вычисляем продолжительность Формирования исходного файла и выводим на экран
    }
    //-------------------------------------------------------------------------------------------------------------------------
    // 
    int* array_from_file = nullptr;

    int n = 25 * size / 10;  // размер массива 25 млн
    array_from_file = new int[n];

    int fsn_exist = 0; // признак наличия исходного файла (1 - есть, 0 - нет)
    if (fsn_exist == 0) {
        auto start2 = chrono::high_resolution_clock::now(); // сохраняем время формирования 8 файлов

        for (int m = 0; m < 8; m++) {


            fi.open(filename, fstream::in);


            // читаем из файла массив 25 млн элементов
            cout << "Промежуточный файл " << filename_sn[m] << endl;

            // читаем 1-й раз 25 млн элементов    
            for (int i = 0; i < n; i++)
                fi >> array_from_file[i]; // читаем из файла разделительные символы - пробел и перенос строки
            countSort(array_from_file, n); // запускаем сортировку подсчетом 

            fs.open(filename_s, fstream::out);

            for (int i = 0; i < n; i++) {
                fs << array_from_file[i] << " "; // записываем отсортированный массив в файл fs
            }
            fs << '\n';
            fs.close(); // закрываем файл


         //-------------------------------------------------------------------------------------------------------------------------

         //   cout << "Чтение в цикле очередных " << "25 млн" << " элементов + сортировка + объединение с файлом s" << endl;

            for (int i = 0; i < n; i++)
                fi >> array_from_file[i]; // читаем из файла разделительные символы - пробел и перенос строки
            countSort(array_from_file, n); // запускаем сортировку подсчетом    
            // for (int i = 0; i < n; i++) cout << array_from_file[i] << " "; cout << endl; //*** --------------------------убрать
            // сравнивая отсортированный массив с файлом fs, формируем отсортированный файл s1 

            fs.open(filename_s, fstream::in);
            fs1.open(filename_sn[m], fstream::out);
            fs >> numb;
            for (int i = 0; i < n; i++) {
                if (array_from_file[i] < numb) fs1 << array_from_file[i] << " ";
                else {
                    while (array_from_file[i] >= numb && !fs.eof()) {
                        fs1 << numb << " ";
                        fs >> numb;
                    }
                    fs1 << array_from_file[i] << " ";
                }
            }
            fs1 << '\n';

            fs1.close(); // закрываем файл
            fs.close(); // закрываем файл

    //        remove("array_data_s1.txt");
    //        rename("array_data_s.txt", "array_data_s1.txt");

            cout << "Сформирован файл s" << m + 1 << ": " << endl << endl; // вычисляем продолжительность работы в сек. и выводим на экран
        }
        auto finish2 = chrono::high_resolution_clock::now(); // сохраняем время конца формирования 8 файлов
        chrono::duration<double> elapsed2 = finish2 - start2;
        cout << "Время формирования 8 файлов : " << elapsed2.count() << " sec" << endl << endl;// вычисляем продолжительность работы в сек. и выводим на экран
    //-------------------------------------------------------------------------

    //-------------------------------------------------------------------------
        fi.close(); // закрываем файл 
    }
    //----------------------объединение 4-х пар промежуточных файлов по 50 млн в 4 файла по 100 млн -----------------------------------------------

    auto start3 = chrono::high_resolution_clock::now(); // сохраняем время начала создания 4 файлов по 100 млн 
    for (int m = 0; m < 4; m++) {
        cout << "Промежуточный файл " << filename_sn2[m] << endl;
        fs1.open(filename_sn[2 * m], fstream::in);
        fs2.open(filename_sn[2 * m + 1], fstream::in);
        fs.open(filename_sn2[m], fstream::out);

        fs2 >> numb2;
        while (!fs1.eof()) {
            fs1 >> numb;
            if (numb < numb2) fs << numb << " ";
            else {
                while (numb >= numb2 && !fs2.eof()) {
                    fs << numb2 << " ";
                    fs2 >> numb2;
                }
                if (!fs1.eof()) fs << numb << " ";
            }
        }
        if (!fs2.eof()) {
            while (!fs2.eof()) {
                fs2 >> numb2;
                if (!fs2.eof()) fs << numb2 << " ";
            }
        }
        fs.close(); // закрываем файл
        fs1.close(); // закрываем файл
        fs2.close(); // закрываем файл
        cout << "Сформирован файл " << filename_sn2[m] << endl << endl; // вычисляем продолжительность работы в сек. и выводим на экран
    }
    auto finish3 = chrono::high_resolution_clock::now(); // сохраняем время конца чтения файла
    chrono::duration<double> elapsed3 = finish3 - start3;
    cout << "Время объединения 4-х пар файлов: " << elapsed3.count() << " sec" << endl << endl; // вычисляем продолжительность работы в сек. и выводим на экран
    cout << "Результат - упорядоченные файлы s12, s34, s56, s78  по "<< 4 * n <<" элементов" << endl;

    //----------------------объединение 2-х пар промежуточных файлов по 100 млн в 2 файла по 200 млн -----------------------------------------------

    auto start4 = chrono::high_resolution_clock::now(); // сохраняем время начала создания 2 файлов по 200 млн 
    for (int m = 0; m < 2; m++) {
        cout << "Промежуточный файл " << filename_sn3[m] << endl;
        fs1.open(filename_sn2[2 * m], fstream::in);
        fs2.open(filename_sn2[2 * m + 1], fstream::in);
        fs.open(filename_sn3[m], fstream::out);

        fs2 >> numb2;
        while (!fs1.eof()) {
            fs1 >> numb;
            if (numb < numb2) fs << numb << " ";
            else {
                while (numb >= numb2 && !fs2.eof()) {
                    fs << numb2 << " ";
                    fs2 >> numb2;
                }
                if (!fs1.eof()) fs << numb << " ";
            }
        }
        if (!fs2.eof()) {
            while (!fs2.eof()) {
                fs2 >> numb2;
                if (!fs2.eof()) fs << numb2 << " ";
            }
        }
        fs.close(); // закрываем файл
        fs1.close(); // закрываем файл
        fs2.close(); // закрываем файл
        cout << "Сформирован файл " << filename_sn3[m] << endl << endl; // вычисляем продолжительность работы в сек. и выводим на экран
    }
    auto finish4 = chrono::high_resolution_clock::now(); // сохраняем время конца чтения файла
    chrono::duration<double> elapsed4 = finish4 - start4;
    cout << "Время объединения 2-х пар файлов: " << elapsed4.count() << " sec" << endl << endl; // вычисляем продолжительность работы в сек. и выводим на экран
    cout << "Результат - упорядоченные файлы s1234, s5678  по " << 8 * n << " элементов" << endl;

    //----------------------объединение 2-х промежуточных файлов по 200 млн в 1 файл 400 млн -----------------------------------------------
    auto start5 = chrono::high_resolution_clock::now(); // сохраняем время начала создания 2 файлов по 200 млн 
    cout << "Окончательный файл " << filename_s << endl;
    fs1.open(filename_sn3[0], fstream::in);
    fs2.open(filename_sn3[1], fstream::in);
    fs.open(filename_s, fstream::out);

    fs2 >> numb2;
    while (!fs1.eof()) {
        fs1 >> numb;
        if (numb < numb2) fs << numb << " ";
        else {
            while (numb >= numb2 && !fs2.eof()) {
                fs << numb2 << " ";
                fs2 >> numb2;
            }
            if (!fs1.eof()) fs << numb << " ";
        }
    }
    if (!fs2.eof()) {
        while (!fs2.eof()) {
            fs2 >> numb2;
            if (!fs2.eof()) fs << numb2 << " ";
        }
    }
    fs.close(); // закрываем файл
    fs1.close(); // закрываем файл
    fs2.close(); // закрываем файл
    cout << "Сформирован окончательный файл " << filename_s << endl << endl; // вычисляем продолжительность работы в сек. и выводим на экран   
    auto finish5 = chrono::high_resolution_clock::now(); // сохраняем время конца чтения файла
    chrono::duration<double> elapsed5 = finish5 - start5;
    cout << "Время объединения 2-х файлов: " << elapsed4.count() << " sec" << endl << endl; // вычисляем продолжительность работы в сек. и выводим на экран
    cout << "Результат - упорядоченный файл array_data_s.txt  - " << 16 * n << " элементов" << endl;
    //-------------------------------------------------------------------------


//  auto start3 = chrono::high_resolution_clock::now(); // сохраняем время начала работы алгоритма
  //***  quickSort(array_from_file, 0, n-1); // запускаем быструю сортировку                     // 100 - 0.0000267 сек   1000 - 0.0011388
  //***  timSort(array_from_file, n); // запускаем сортировку вставки + слияние                  // 100 - 0.0000267 сек   1000 - 0.0011388
  //***  mergeSort(array_from_file, 0, n-1); // запускаем сортировку слияние                  // 100 - 0.0000267 сек   1000 - 0.0011388
  //***  insertionSort(array_from_file, 0, n-1); // запускаем сортировку вставками               // 100 - 0.0000074 сек   1000 - 0.0005226
  //***  selectionSort(array_from_file, n); // запускаем сортировку выбором                  // 100 - 0.0000168 sec   1000 - 0.0019643
  //***  bubbleSort(array_from_file, n); // запускаем сортировку пузырьки                           // 100 - 0.0000168 sec   1000 - 0.0019643
  //***   bucketSort(array_from_file, n); // запускаем сортировку карманы                          // 100 - 0.0000168 sec   1000 - 0.0019643
  //***  countSort(array_from_file, n); // запускаем сортировку подсчетом                         // 100 - 0.0000168 sec   1000 - 0.0019643

//   auto finish3 = chrono::high_resolution_clock::now(); // сохраняем время конца работы алгоритма
//   chrono::duration<double> elapsed3 = finish3 - start3;
//   cout << "Время сортировки: " << elapsed3.count() << " sec" << endl; // вычисляем продолжительность работы в сек. и выводим на экран

//   auto start4 = chrono::high_resolution_clock::now(); // сохраняем время начала формирования выходного файла
//    fs.open(filename_s, fstream::out);

    // const int size = 10000000;

    //int* rand_arr = new int[size];

 //   const int new_size = 30000000;
 //   for (int i = 0; i < new_size; i++) {
 //       fs << array_from_file[i] << ' '; // записываем значения через пробел
 //   }

 //   fs << '\n';

//    cout << "end array_s.txt" << endl;
//    fs.close(); // закрываем файл
//    auto finish4 = chrono::high_resolution_clock::now(); // сохраняем время конца формирования выходного файла
//    chrono::duration<double> elapsed4 = finish4 - start4;
 //   cout << "Формирование выходного файла: " << elapsed4.count() << " sec" << endl; // вычисляем продолжительность Формирования исходного файла и выводим на экран
 //   write_arr(filename_s, array_from_file, size); // записываем массив после сортировки в файл

    delete[] array_from_file;
    return 0;
}
