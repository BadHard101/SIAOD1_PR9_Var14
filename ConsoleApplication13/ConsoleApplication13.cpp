#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

string filee = "binfile.bin";

struct table
{
    int id, address;
};
struct city
{
	int id;
	string name;
};
bool cmp(table& a, table& b) {
    if (a.id < b.id) return true;
    return false;
}

string fnd_cty_by_id(int find_id) {
	city* c = new city;
	ifstream binFile2(filee, ios::binary);
	while (binFile2.read((char*)c, sizeof(city)))
		if (c->id == find_id) {
			binFile2.close();
			return c->name;
		}
	return "-1";
}

int min(int x, int y) { return (x <= y) ? x : y; }

/* Returns index of x if present,  else returns -1 */
int fibMonaccianSearch(vector<table> arr, int x, int n)
{
    /* Initialize fibonacci numbers */
    int fibMMm2 = 0; // (m-2)'th Fibonacci No.
    int fibMMm1 = 1; // (m-1)'th Fibonacci No.
    int fibM = fibMMm2 + fibMMm1; // m'th Fibonacci

    /* fibM is going to store the smallest Fibonacci
       Number greater than or equal to n */
    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    // Marks the eliminated range from front
    int offset = -1;

    /* while there are elements to be inspected. Note that
       we compare arr[fibMm2] with x. When fibM becomes 1,
       fibMm2 becomes 0 */
    while (fibM > 1) {
        // Check if fibMm2 is a valid location
        int i = min(offset + fibMMm2, n - 1);

        /* If x is greater than the value at index fibMm2,
           cut the subarray array from offset to i */
        if (arr[i].id < x) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }

        /* If x is greater than the value at index fibMm2,
           cut the subarray after i+1  */
        else if (arr[i].id > x) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }

        /* element found. return index */
        else
            return arr[i].address;
    }

    /* comparing the last element with x */
    if (fibMMm1 && arr[offset + 1].id == x)
        return arr[offset + 1].address;

    /*element not found. return -1 */
    return -1;
}

void create_file(int N,int a,int b,vector<table>& vec) {
    ofstream binFile(filee, ios::binary);
    cout << binFile.is_open() << endl;
    for (int i = 0; i < N; i++)
    {
        bool flag = true;
        int x = rand() % (b - a + 1) + a;
        if (vec.size() != 0) {
            while (flag)
            {
                int f = 0;
                for (int i = 0; i < vec.size(); i++)
                {
                    if (vec[i].id == x) {
                        x++;
                        break;
                      
                    }

                }
                flag = false;
            }
        }
        city c;
        table cc = { x, i };
        c.id = x;
        c.name = "Moscow" + to_string(i);
        vec.push_back(cc);
        binFile.write((char*)&c, sizeof(city));
    }
    binFile.close();
}
void read_file(vector<table>&vec) {
    city* c = new city;
    ifstream binFile2(filee, ios::binary);
    //int index = 0;
    while (binFile2.read((char*)c, sizeof(city))) {
        cout << c->id << " " << c->name << endl;
        //table cc = { c->id, index };
        //vec.push_back(cc);
        //index += 1;
    }
    binFile2.close();
}

void seek(vector<table>vec, int N, int x) {
    sort(vec.begin(), vec.end(), cmp);

    /*for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i].id << " " << vec[i].address << endl;
    }*/

    int adres = fibMonaccianSearch(vec, x, N);

    /*if (adres >= 0)
        printf("Found at address: %d", adres);
    else
        printf("%d isn't present in the array", x);
    cout << endl;
    */

    city* c = new city;
    ifstream binFile3(filee, ios::binary);
    binFile3.seekg(adres * sizeof(city), SEEK_SET);
    binFile3.read((char*)c, sizeof(city));
    cout << c->name << endl;
}
int main()
{
	int a = 10000;
	int b = 99999;
	srand(time(NULL)); 
    int N = 100;
    cout << "Enter number of records: ";
    cin >> N;
    int x;
    vector<table> vec;
    int menu = 5;
    string c;
    unsigned int start_time;
    unsigned int end_time;

    while (menu != 0) {
        cout << "1 - Create file\n"
            << "2 - Read file\n"
            << "3 - Fibonachi search\n"
            << "4 - Linear search\n"
            << "0 - Exit\n"
            << "Enter: ";
        cin >> menu;
        switch (menu) {
        case 1:
            create_file(N, a, b, vec);
            break;
        case 2:
            cout << "\nList of cities:\n";
            read_file(vec);
            cout << endl;
            break;
        case 3:
            cout << endl << "Enter a num: ";
            cin >> x;
            start_time = clock();
            seek(vec,N,x);
            end_time = clock();
            cout << endl;
            cout << "time: "
                << (end_time - start_time) / 1000.0
                << " sec\n\n"; 
            break;
        case 4:
            cout << endl << "Enter a num: ";
            cin >> x;
            start_time = clock();
            c = fnd_cty_by_id(x);
            end_time = clock();
            if (c != "-1")
                cout << c << endl << endl;
            else
                cout << endl;
            cout << "time: "
                << (end_time - start_time) / 1000.0
                << " sec\n\n";
            break;
        default:
            cout << "It's me, Mario!" << endl << endl;
        }
    };
}