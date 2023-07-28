// EN.605.604.SU23_Assignment3.cpp

#include "Array.h"

using namespace std;

int main()
{
    cout << fixed << setprecision(2);
    cout << "Assignment 3 - (Template: Array)" << endl;

    cout << endl << "[int]" << endl;
    cout << "##### Array<int> intdata{ 2 }, intdata[0] = 123 #####" << endl;
    Array<int> intdata{ 2 };
    intdata[0] = 123;
    intdata.display();
    cout << "##### Array<int> intdata2{ -intdata } #####" << endl;
    Array<int> intdata2{ -intdata };
    intdata2.display();
    cout << "##### Array<int> intdata3 = intdata + intdata2 #####" << endl;
    Array<int> intdata3 = intdata + intdata2;
    intdata3.display();
    cout << "##### intdata4(1), intdata4[0] = 777 #####" << endl;
    Array<int> intdata4(1);
    intdata4[0] = 777;
    intdata4.display();
    cout << "##### intdata2 = -intdata4 #####" << endl;
    intdata2 = -intdata4;
    intdata2.display();
    cout << "##### intdata4 = intdata + intdata2 #####" << endl;
    intdata4 = intdata + intdata2;
    intdata4.display();

    cout << endl << "[float]" << endl;
    cout << "##### Array<float> fdata{ 2 } #####" << endl;
    Array<float> fdata{ 2 };
    fdata[0] = 1.23f;
    fdata.display();
    cout << "##### Array<float> fdata2{ -fdata } #####" << endl;
    Array<float> fdata2{ -fdata };
    fdata2.display();
    cout << "##### Array<float> fdata3 = fdata + fdata2 #####" << endl;
    Array<float> fdata3 = fdata + fdata2;
    fdata3.display();
    cout << "##### Array<float> fdata4(1) #####" << endl;
    Array<float> fdata4(1);
    fdata4[0] = 3.14159f;
    fdata4.display();
    cout << "##### fdata4 = -fdata4 + fdata #####" << endl;
    fdata4 = -fdata4 + fdata;
    fdata4.display();

    cout << endl << "[string]" << endl;
    cout << "##### Array<string> sdata{ 2 }, sdata[0] = \"Hello\" #####" << endl;
    Array<string> sdata{ 2 }; // Array of 3 strings
    sdata[0] = "Hello";
    sdata.display();
    cout << "##### Array<string> sdata2{ sdata }, sdata2[1] = \"World\" #####" << endl;
    Array<string> sdata2{ sdata };
    sdata2[1] = "World";
    sdata2.display();
    cout << "##### Array<string> sdata3 = sdata1 + sdata2 #####" << endl;
    Array<string> sdata3 = sdata + sdata2;
    sdata3.display();
    cout << "##### Array<string> sdata4(1), sdata4[0] = \"Nice\" #####" << endl;
    Array<string> sdata4(1);
    sdata4[0] = "Nice";
    sdata4.display();
    cout << "##### Array<string> sdata4 = sdata4 + sdata3 #####" << endl;
    sdata4 = sdata4 + sdata3;
    sdata4.display();

    cout << endl << "[Date]" << endl;
    cout << "##### Array<Date> ddata{ 2 }, ddata[0] = Date(23, 7, 2023) #####" << endl;
    Array<Date> ddata{ 2 };
    ddata[0] = Date(23, 7, 2023);
    ddata.display();
    cout << "##### Array<Date> ddata2{ ddata }, ddata2[1] = Date(25, 12, 1234) #####" << endl;
    Array<Date> ddata2{ ddata };
    ddata2[1] = Date(25, 12, 1234);
    ddata2.display();
    cout << "##### Array<Date> ddata3 = ddata2, ddata3[0].setYear(7777) #####" << endl;
    Array<Date> ddata3 = ddata2;
    ddata3[0].setYear(7777);
    ddata3.display();
    cout << "##### Array<Date> ddata4{ 1 } #####" << endl;
    Array<Date> ddata4{ 1 };
    ddata4.display();
    cout << "##### ddata4 = ddata3 #####" << endl;
    ddata4 = ddata3;
    ddata4.display();

    return 0;
}
