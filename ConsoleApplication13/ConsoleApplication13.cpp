#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
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

city* fnd_cty_by_id(int find_id) {
	city* c = new city;
	ifstream binFile2(filee, ios::binary);
	while (binFile2.read((char*)c, sizeof(city)))
		if (c->id == find_id) {
			binFile2.close();
			return c;
		}
	return nullptr;
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

void Create_file() {

}

int main()
{

	int a = 99;
	int b = 998;
	srand(time(NULL));
    int N = 100;

    vector<table> vec;
 
	/*ofstream binFile(filee, ios::binary);
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
                        f = 1;
                        break;
                    }
                    flag = false;
                }
                if (f == 0)
                    break;
                x++;
            }
        }
		city c;
        table cc = {x, i};
		c.id = x;
		c.name = "Moscow"+to_string(i);
        vec.push_back(cc);
		binFile.write((char*)&c, sizeof(city));
	}
	binFile.close();*/

	city* c = new city;
	ifstream binFile2(filee, ios::binary);
    int index = 0;
    while (binFile2.read((char*)c, sizeof(city))) {
        cout << c->id << " " << c->name << endl;
        table cc = { c->id, index };
        vec.push_back(cc);
        index += 1;
    }
	binFile2.close();

    sort(vec.begin(),vec.end(), cmp);
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i].id << " " << vec[i].address << endl;
    }
    
    int x = 736;
    int adres = fibMonaccianSearch(vec, x, N);
    if (adres >= 0)
        printf("Found at adres: %d", adres);
    else
        printf("%d isn't present in the array", x);

    cout << endl;
    city* link = new city;
    ifstream binFile3(filee, ios::binary);
    binFile3.seekg(adres * sizeof(city), SEEK_SET);
    binFile3.read((char*)c, sizeof(city));
    cout << c->id << " " << c->name << endl;
    /*
    if (fnd_cty_by_id(x))
        cout << fnd_cty_by_id(x) << endl;*/
}