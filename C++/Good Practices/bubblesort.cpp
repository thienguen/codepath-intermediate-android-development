
#include <iostream>
#include <iomanip>
using namespace std; 

int main() {
	const int arraySize = 10; //Size of array a
	int a[arraySize] = {2, 6, 4, 8, 10, 12, 89, 68, 45, 37};
	int hold; 				  //Temporary location used to swap array elements

	cout << "Data items in original order\n";

	//Output original array
	for (int i = 0; i < arraySize; i++)
		cout << setw(4) << a[i];

	//Bubble sort
	//Loop to control number of passes
	for (int i = 0; i < arraySize - 1; i++) {
		//Loop to control number of comparisons per pass
		for (int j = 0; j < arraySize - i - 1; j++) {
			//Compare side-by-side elements and swap them if first element is greater than second element
			if (a[j] > a[j + 1]) {
				hold = a[j];    //Place element a[j] in hold.
				a[j] = a[j + 1];  //Element a[j] takes a[j+1] value.
				a[j + 1] = hold;  //a[j+1] takes a[j] value from temp hold.
			}
		}
	}

	cout << "\nData items in ascending order\n";

	//Output sorted array
	for (int k = 0; k < arraySize; k++)
		cout << setw(4) << a[k];

	cout << endl;
    return EXIT_SUCCESS;
}
