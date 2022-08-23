#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

long long int square_and_multiply(long long int base, int exponent, int modulo)
{
    long long int ans = 1;
    base = base % modulo; // reduce the base so that it is less than modulo
    while (exponent > 0)
    {
        if (exponent & 1) // if the exponent is odd
        {
            ans = (ans * base) % modulo;
        }
        exponent >>= 1; // divide by 2
        base = base * base % modulo;
    }
    return ans;
}

string encryptMessage(string str, long long int n, long long e)
{
    string result = "";
    const int block_size = 3;
    int quotient = str.length() / block_size;
    int remainder = str.length() % block_size;
    string hex[quotient + 1];
    int k = 0;

    for (int i = 0, l = 0; l < quotient; i += block_size, k++, l++)
    {
        string temp1 = "";
        for (int j = 0; j < block_size; j++)
        {
            stringstream temp2;
            int ch = (int)str[i + j];
            temp2 << std::hex << ch; // use std::hex NOT hex alone
            temp1 += temp2.str();
            temp2.str(string()); // clear the stringstream
        }
        hex[k] = temp1;
    }
    string temp1 = "";
    for (int i = block_size * quotient; i < str.length(); i++)
    {
        stringstream temp2;
        int ch = (int)str[i];
        temp2 << std::hex << ch;
        temp1 += temp2.str();
    }
    hex[k] = temp1;
    for (int i = 0; i < quotient + 1; i++)
    {
        if (hex[i].compare("") != 0)
        {
            result += to_string(square_and_multiply(stoi(hex[i], 0, 16), e, n));
            result += ",";
        }
    }
    return result.substr(0, result.length() - 1);
}

string decryptMessage(long long int *inp, long long int n, long long d, int len)
{
    string result = "";
    for (int i = 0; i < len; i++)
    {
        stringstream temp;
        int num = square_and_multiply(inp[i], d, n);
        temp << std::hex << num;
        string x = temp.str();
        for (int i = 0; i < x.length(); i += 2)
        {
            result += (char)stoi(x.substr(i, 2), 0, 16);
        }
    }
    return result;
}

int main()
{
    string msg = "";
    long long int n;
    long long int exponent = 0;
    bool choice = 1;
    string output = "";

    cout << "Enter 1 to encrpt the meessage and 0 to decrypt it" << endl;
    cin >> choice;

    if (choice)
    {
        cout << "Please input the message to be encrypted" << endl;
        getline(cin, msg);
        getline(cin, msg);
    }

    cout << "Please input the value of n" << endl;
    cin >> n;

    choice ? cout << "Please input the value of e" << endl : cout << "Please input the value of d" << endl;

    cin >> exponent;

    if (choice)
    {
        output = encryptMessage(msg, n, exponent);
        cout << output << endl;
    }
    else
    {
        // d = 209111611;
        // n = 1322748923;
        // e = 1392327451;
        // msg = hi how are you
        // msg = Hello Prathiksha, what's up with you these days?
        // msg = Hi , I am here !
        // long long int nums[] = {1569787125, 590844351, 451112047, 1446084848, 1122776505};
        // long long int nums[] = {331732113,659252484,492771721,447411906,1320342502,473739106};
        // long long int nums[] = {166270295, 1132606128, 907572347, 27829723, 931228010, 451934055, 950962358, 220958389, 108009823, 757844291, 974919726, 286516310, 259278350, 1058285732, 216959605, 855215051};
        // long long int nums[] = {426533117,449505729,636154792,1037027525,1113978882,209459562};
        long long int nums[] = {34448243, 1834978996, 1289803449, 1634926748, 60891344, 1581660850, 1642030706, 1965598360};
        int len = sizeof(nums) / sizeof(long long int);
        output = decryptMessage(nums, n, exponent, len);
        cout << "Decrypted message: " << output << endl;
    }
}
