#include<iostream>
#include<iomanip>

using namespace std;

int main(){
    int size = 5;
    for (int i = 0; i < size; i++)
    {
        cout << " _____";
    }
    cout << "\n";
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << "|     ";
        }
        cout << "|\n";
        for (int j = 0; j < size; j++)
        {
            cout << "|" << " " << setw(4) << left << 5;
        }
        cout << "|\n";
        for (int j = 0; j < size; j++)
        {
            cout << "|_____";
        }
        cout << "|\n";
    }
    cout << endl;
}