// ���������� �������� �������
#include <string>
#include <fstream>  // ������ � �������
#include <iostream>
#include <cstdlib> // ��� ��������� ��������� �����
#include <ctime>
#include <chrono>
#include <stdio.h>

using namespace std;

struct bucket {
    int count; // ���������� ��������� � �������
    int* data; // ������ ��������� �������
};

void write_arr(const string& filename, const int* arr, const int n)
{
    fstream fs;

    fs.open(filename, fstream::out);
    if (fs.is_open()) // ���������, ��� ���� ������� ������
    {
        fs << n << '\n';  // ���������� ������ �������
        for (int i = 0; i < n; i++)
            fs << arr[i] << ' '; // ���������� �������� ����� ������
        fs << '\n';

        fs.close(); // ��������� ����
    }
}

void read_arr(const string& filename, int*& arr, int& n)
{
    fstream fs;

    fs.open(filename, fstream::in);
    if (fs.is_open()) // ���������, ��� ���� ������� ������
    {
        fs >> n;  // ������ ������ �������
        arr = new int[n];
        for (int i = 0; i < n; i++)
            fs >> arr[i]; // ������ �� ����� �������������� ������� - ������ � ������� ������

        fs.close(); // ��������� ����
    }
}

void swap(int* a, int* b) // ������� ��� ����� ������� ���� ��������
{
    int temp = *a;
    *a = *b;
    *b = temp;
}



//=============================================================================================================
int getMax(int* arr, int n) // ������� ���������� ������������� �������� �������
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
        count[arr[i]]++;  // ������������  ������� ���������� ���������

    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];  // ��������� ����������� �����

    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];  // ������������� ������� �� ���������� ����� 
        count[arr[i]]--; // ��������� �������, ��� ��� ��� �������� �������
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];

    delete[] output;
    delete[] count;
}

//=============================================================================================================
// ������������ ��������� �����: 39 ��� ��������� �� 10 ��� ���������
// ����������: 1) ������ 30 ��� ��������� � ������, ���������, ���������� � ���� array_data_s
//             2) � ����� ������ ��������� 30 ��� ��������� � ������, ���������, 
//                ���������� � ������ array_data_s � ���� array_data_s1, 
//                ��������������� array_data_s1 � array_data_s
int main()
{
    string filename = "array_data_2_Gb.txt";   // �������� ����
    string filename_s = "array_data_s.txt";   // �������� ��������������� ����
    string filename_s1 = "array_data_s1.txt"; // ����, ������������ ��������� ��������������� ������ � �������� ��������������� ������
    string filename_s2 = "array_data_s2.txt"; // ����, ������������ ��������� ��������������� ������ � �������� ��������������� ������
    string filename_sn[8] = { "s1.txt","s2.txt","s3.txt","s4.txt","s5.txt","s6.txt","s7.txt","s8.txt" }; // ������������� ��������������� ����� �� 50 ���
    string filename_sn2[4] = { "s12.txt","s34.txt","s56.txt","s78.txt" }; // ������������� ��������������� ����� �� 100 ���
    string filename_sn3[2] = { "s1234.txt","s5678.txt" }; // ������������� ��������������� ����� �� 200 ���

    fstream fi;
    fstream fs;
    fstream fs1;
    fstream fs2;
    int numb, numb2;                                 // ������� �����


    int k = 40;  // ���-�� ������ �� 10 ��� ��� ������������ ��������� ������� 2��

    setlocale(LC_ALL, "");

    //-------------------------------------------------------------------------------------------------------------------------
    const int size = 10000000;
    int fi_exist = 0; // ������� ������� ��������� ����� (1 - ����, 0 - ���)
    if (fi_exist == 0) {

        auto start1 = chrono::high_resolution_clock::now(); // ��������� ����� ������ ������������ ��������� �����

        fi.open(filename, fstream::out);

        int* rand_arr = new int[size];
        // ���������� � ���� 40 ��� �� 10 ��� ���������
        cout << "���������� � �������� ���� " << k << " ��� �� " << size << " ���������" << endl;
        for (int j = 0; j < k; j++) {
            cout << j + 1 << endl;
            srand(time(nullptr)); // ���������� ������� �����, ����� ������������� ��������� ��������
            int lef_border = 1;
            int range_len = 30000 + 50 * j + 1; // ������ ������� = range_len + left_border      30000 + 50 * j + 1
                                                // range_len � ����� ��������, ����� ��������� ���� ��������� ���� ������� ��������� �� ����������
            for (int i = 0; i < size; i++) {
                rand_arr[i] = lef_border + rand() % range_len; // ���������� ����� � ��������� ��������� � ���������� � ������
                fi << rand_arr[i] << ' '; // ���������� �������� ����� ������
            }

            fi << '\n';
        }
        cout << "����������� �������� ���� array_data_2_Gb.txt" << endl;
        fi.close(); // ��������� ����
        delete[] rand_arr;

        auto finish1 = chrono::high_resolution_clock::now(); // ��������� ����� ����� ������������ ��������� �����
        chrono::duration<double> elapsed1 = finish1 - start1;
        cout << "����� ������������ ��������� �����: " << elapsed1.count() << " sec" << endl << endl; // ��������� ����������������� ������������ ��������� ����� � ������� �� �����
    }
    //-------------------------------------------------------------------------------------------------------------------------
    // 
    int* array_from_file = nullptr;

    int n = 25 * size / 10;  // ������ ������� 25 ���
    array_from_file = new int[n];

    int fsn_exist = 0; // ������� ������� ��������� ����� (1 - ����, 0 - ���)
    if (fsn_exist == 0) {
        auto start2 = chrono::high_resolution_clock::now(); // ��������� ����� ������������ 8 ������

        for (int m = 0; m < 8; m++) {


            fi.open(filename, fstream::in);


            // ������ �� ����� ������ 25 ��� ���������
            cout << "������������� ���� " << filename_sn[m] << endl;

            // ������ 1-� ��� 25 ��� ���������    
            for (int i = 0; i < n; i++)
                fi >> array_from_file[i]; // ������ �� ����� �������������� ������� - ������ � ������� ������
            countSort(array_from_file, n); // ��������� ���������� ��������� 

            fs.open(filename_s, fstream::out);

            for (int i = 0; i < n; i++) {
                fs << array_from_file[i] << " "; // ���������� ��������������� ������ � ���� fs
            }
            fs << '\n';
            fs.close(); // ��������� ����


         //-------------------------------------------------------------------------------------------------------------------------

         //   cout << "������ � ����� ��������� " << "25 ���" << " ��������� + ���������� + ����������� � ������ s" << endl;

            for (int i = 0; i < n; i++)
                fi >> array_from_file[i]; // ������ �� ����� �������������� ������� - ������ � ������� ������
            countSort(array_from_file, n); // ��������� ���������� ���������    
            // for (int i = 0; i < n; i++) cout << array_from_file[i] << " "; cout << endl; //*** --------------------------������
            // ��������� ��������������� ������ � ������ fs, ��������� ��������������� ���� s1 

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

            fs1.close(); // ��������� ����
            fs.close(); // ��������� ����

    //        remove("array_data_s1.txt");
    //        rename("array_data_s.txt", "array_data_s1.txt");

            cout << "����������� ���� s" << m + 1 << ": " << endl << endl; // ��������� ����������������� ������ � ���. � ������� �� �����
        }
        auto finish2 = chrono::high_resolution_clock::now(); // ��������� ����� ����� ������������ 8 ������
        chrono::duration<double> elapsed2 = finish2 - start2;
        cout << "����� ������������ 8 ������ : " << elapsed2.count() << " sec" << endl << endl;// ��������� ����������������� ������ � ���. � ������� �� �����
    //-------------------------------------------------------------------------

    //-------------------------------------------------------------------------
        fi.close(); // ��������� ���� 
    }
    //----------------------����������� 4-� ��� ������������� ������ �� 50 ��� � 4 ����� �� 100 ��� -----------------------------------------------

    auto start3 = chrono::high_resolution_clock::now(); // ��������� ����� ������ �������� 4 ������ �� 100 ��� 
    for (int m = 0; m < 4; m++) {
        cout << "������������� ���� " << filename_sn2[m] << endl;
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
        fs.close(); // ��������� ����
        fs1.close(); // ��������� ����
        fs2.close(); // ��������� ����
        cout << "����������� ���� " << filename_sn2[m] << endl << endl; // ��������� ����������������� ������ � ���. � ������� �� �����
    }
    auto finish3 = chrono::high_resolution_clock::now(); // ��������� ����� ����� ������ �����
    chrono::duration<double> elapsed3 = finish3 - start3;
    cout << "����� ����������� 4-� ��� ������: " << elapsed3.count() << " sec" << endl << endl; // ��������� ����������������� ������ � ���. � ������� �� �����
    cout << "��������� - ������������� ����� s12, s34, s56, s78  �� "<< 4 * n <<" ���������" << endl;

    //----------------------����������� 2-� ��� ������������� ������ �� 100 ��� � 2 ����� �� 200 ��� -----------------------------------------------

    auto start4 = chrono::high_resolution_clock::now(); // ��������� ����� ������ �������� 2 ������ �� 200 ��� 
    for (int m = 0; m < 2; m++) {
        cout << "������������� ���� " << filename_sn3[m] << endl;
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
        fs.close(); // ��������� ����
        fs1.close(); // ��������� ����
        fs2.close(); // ��������� ����
        cout << "����������� ���� " << filename_sn3[m] << endl << endl; // ��������� ����������������� ������ � ���. � ������� �� �����
    }
    auto finish4 = chrono::high_resolution_clock::now(); // ��������� ����� ����� ������ �����
    chrono::duration<double> elapsed4 = finish4 - start4;
    cout << "����� ����������� 2-� ��� ������: " << elapsed4.count() << " sec" << endl << endl; // ��������� ����������������� ������ � ���. � ������� �� �����
    cout << "��������� - ������������� ����� s1234, s5678  �� " << 8 * n << " ���������" << endl;

    //----------------------����������� 2-� ������������� ������ �� 200 ��� � 1 ���� 400 ��� -----------------------------------------------
    auto start5 = chrono::high_resolution_clock::now(); // ��������� ����� ������ �������� 2 ������ �� 200 ��� 
    cout << "������������� ���� " << filename_s << endl;
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
    fs.close(); // ��������� ����
    fs1.close(); // ��������� ����
    fs2.close(); // ��������� ����
    cout << "����������� ������������� ���� " << filename_s << endl << endl; // ��������� ����������������� ������ � ���. � ������� �� �����   
    auto finish5 = chrono::high_resolution_clock::now(); // ��������� ����� ����� ������ �����
    chrono::duration<double> elapsed5 = finish5 - start5;
    cout << "����� ����������� 2-� ������: " << elapsed4.count() << " sec" << endl << endl; // ��������� ����������������� ������ � ���. � ������� �� �����
    cout << "��������� - ������������� ���� array_data_s.txt  - " << 16 * n << " ���������" << endl;
    //-------------------------------------------------------------------------


//  auto start3 = chrono::high_resolution_clock::now(); // ��������� ����� ������ ������ ���������
  //***  quickSort(array_from_file, 0, n-1); // ��������� ������� ����������                     // 100 - 0.0000267 ���   1000 - 0.0011388
  //***  timSort(array_from_file, n); // ��������� ���������� ������� + �������                  // 100 - 0.0000267 ���   1000 - 0.0011388
  //***  mergeSort(array_from_file, 0, n-1); // ��������� ���������� �������                  // 100 - 0.0000267 ���   1000 - 0.0011388
  //***  insertionSort(array_from_file, 0, n-1); // ��������� ���������� ���������               // 100 - 0.0000074 ���   1000 - 0.0005226
  //***  selectionSort(array_from_file, n); // ��������� ���������� �������                  // 100 - 0.0000168 sec   1000 - 0.0019643
  //***  bubbleSort(array_from_file, n); // ��������� ���������� ��������                           // 100 - 0.0000168 sec   1000 - 0.0019643
  //***   bucketSort(array_from_file, n); // ��������� ���������� �������                          // 100 - 0.0000168 sec   1000 - 0.0019643
  //***  countSort(array_from_file, n); // ��������� ���������� ���������                         // 100 - 0.0000168 sec   1000 - 0.0019643

//   auto finish3 = chrono::high_resolution_clock::now(); // ��������� ����� ����� ������ ���������
//   chrono::duration<double> elapsed3 = finish3 - start3;
//   cout << "����� ����������: " << elapsed3.count() << " sec" << endl; // ��������� ����������������� ������ � ���. � ������� �� �����

//   auto start4 = chrono::high_resolution_clock::now(); // ��������� ����� ������ ������������ ��������� �����
//    fs.open(filename_s, fstream::out);

    // const int size = 10000000;

    //int* rand_arr = new int[size];

 //   const int new_size = 30000000;
 //   for (int i = 0; i < new_size; i++) {
 //       fs << array_from_file[i] << ' '; // ���������� �������� ����� ������
 //   }

 //   fs << '\n';

//    cout << "end array_s.txt" << endl;
//    fs.close(); // ��������� ����
//    auto finish4 = chrono::high_resolution_clock::now(); // ��������� ����� ����� ������������ ��������� �����
//    chrono::duration<double> elapsed4 = finish4 - start4;
 //   cout << "������������ ��������� �����: " << elapsed4.count() << " sec" << endl; // ��������� ����������������� ������������ ��������� ����� � ������� �� �����
 //   write_arr(filename_s, array_from_file, size); // ���������� ������ ����� ���������� � ����

    delete[] array_from_file;
    return 0;
}
