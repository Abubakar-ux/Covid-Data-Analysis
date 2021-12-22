#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
using namespace std;

struct Node {
	string *date = new string[100];
	string ID;
	string name;
	string region;
	int* deaths = new int[100];
	int* cumulativeDeaths = new int[100];
	int* confirmed = new int[100];
	int* cumulativeConfirmed = new int[100];
	int size = 0; //actual sizes for all arrays.
	int score;
	Node* next;
};

struct List {
	Node *head;
};

List dataSet;

void fileRead() {
	ifstream fileOpener("WHO-COVID-19.csv");
	string date, ID, region, line, name;
	char integers[50];
	int deaths = 0,cumulDeaths = 0,confirmed = 0,cumulativeConfirmed = 0;
	int i = 0, counter = 0;
	while (1) {
	
		int checker = 0;
			
		if (i == 0) {
			getline(fileOpener, line);
		}
		getline(fileOpener,date,',');
		getline(fileOpener,ID,',');
		getline(fileOpener,name,',');
		getline(fileOpener,region,',');
		fileOpener.getline(integers,50);

		
		if(fileOpener.eof()) break;

		char* token = strtok(integers,",");
		deaths = atoi(integers);
		while(token != NULL) {
			if(checker == 1)
				cumulDeaths = atoi(token);
			else if(checker == 2)
				confirmed = atoi(token);
			else if(checker == 3)
				cumulativeConfirmed = atoi(token);			
			token = strtok(NULL,",");
			checker++;
		}
		
		if(name == "undefined")
			continue;

		if(i == 0) {
			Node *newNode = new Node;
			newNode->next = NULL;
			newNode->ID = ID;
			newNode->name = name;
			newNode->region = region;
			newNode->date[counter] = date;
			newNode->deaths[counter] = deaths;
			newNode->cumulativeDeaths[counter] = cumulDeaths;
			newNode->confirmed[counter] = confirmed;
			newNode->cumulativeConfirmed[counter] = cumulativeConfirmed;
			newNode->size++;
			dataSet.head = newNode;
			counter++;
			i++;
		}	
		
		else {
			Node* temp = dataSet.head;
			
			while(temp->next)
				temp = temp->next;

			if(name == temp->name) {
				temp->date[counter] = date;
				temp->deaths[counter] = deaths;
				temp->cumulativeDeaths[counter] = cumulDeaths;
				temp->confirmed[counter] = confirmed;
				temp->cumulativeConfirmed[counter] = cumulativeConfirmed;
				counter++;
				temp->size++;
			}
			else {
				counter = 0;
				Node* newNode = new Node;
				newNode->next = NULL;
				newNode->ID = ID;
				newNode->name = name;
				newNode->region = region;
				newNode->date[counter] = date;
				newNode->deaths[counter] = deaths;
				newNode->cumulativeDeaths[counter] = cumulDeaths;
				newNode->confirmed[counter] = confirmed;
				newNode->cumulativeConfirmed[counter] = cumulativeConfirmed;
				newNode->size++;
				while(temp->next) {
					temp = temp->next;
				}
				temp->next = newNode;
				counter++;
			}
		}
	}
	
	fileOpener.close();

	ifstream file("CountryWeight.csv");
	Node* nodePtr = dataSet.head;
	string avoid;
	getline(file,avoid);
	int score;
	while(nodePtr) {
		getline(file,name,',');
		file.getline(integers,50);
		
		char* token = strtok(integers,",");
		score = atoi(integers);		
	
		if(nodePtr->name == name) {
			nodePtr->score = score;
		}
		nodePtr = nodePtr->next;
	}	
	
	file.close();

}

struct Confirmed{
	string name;
	int cases;
	
	Confirmed() {
		name = "";
		cases = 0;
	}
};

template<class T>
void swap(T *a, T *b) {
	T temp = *a;
	*a = *b;
	*b = temp;
}

int partition(Confirmed arr[], int low, int high) {
	int pivot = arr[high].cases;
	int i = (low - 1);
	
	for(int j = low; j<=high-1; j++) {
		if(arr[j].cases >= pivot) {
			i++;
			swap(&arr[i].cases,&arr[j].cases);
			swap(&arr[i].name,&arr[j].name);
		}
	}

	swap(&arr[i+1].cases,&arr[high].cases);	
	swap(&arr[i+1].name,&arr[high].name);
	return (i+1);
}

void quickSort(Confirmed arr[], int low, int high) {
	if(low < high) {
		int pi = partition(arr,low,high);
		quickSort(arr, low, pi-1);
		quickSort(arr, pi+1, high);
	}
}

void case1(string &date) {
	Node *nodePtr = dataSet.head;
	Confirmed *countries = new Confirmed[256];
	int counter = 0;
	while(nodePtr) {
		for(int i = 0; i<nodePtr->size; i++) {
			if(nodePtr->date[i] == date) {
				countries[counter].name = nodePtr->name;
				countries[counter].cases = nodePtr->confirmed[i];
				counter++;			
				break; // We do not scan it till O(N). As soon as our matching date cases are stored, we break the loop.
			}
		}
		nodePtr = nodePtr->next; // Move on to the next country statistics.
	}

	quickSort(countries,0,counter-1); // we will use quickSort for sorting as it gives O(nLogn) in avg case and is much better and efficient for huge dataSets.

	cout << "Top 20 countries with most confirmed cases on the date provided are:-" << endl;
	for(int i = 0; i<20; i++){
		if(countries[i].name == "")
			break;
		cout << countries[i].name << " " << countries[i].cases << endl;	
	} 
}

void case2(string &startDate, string &endDate) {
	Node *nodePtr = dataSet.head;
	Confirmed country;
	string name;
	int temp = 0, newCases = 0;
	bool startCheck;
	bool endCheck;
	while(nodePtr) {
		startCheck = false;
		endCheck = false;
		for(int i = 0; i<nodePtr->size; i++) {
			if(nodePtr->date[i] == startDate) {
				startCheck = true;
				temp = nodePtr->cumulativeConfirmed[i-1];
			}
			else if(nodePtr->date[i] == endDate) {
				if(startCheck) {				
					name = nodePtr->name;
					newCases = nodePtr->cumulativeConfirmed[i] - temp;
					endCheck = true;
					break;
				}
			}
		}
		if(newCases > country.cases) {
			country.name = name;
			country.cases = newCases;
		}
		nodePtr = nodePtr->next;
	}
	
	cout << country.name << " with most new confirmed cases " << country.cases << endl;
	
	
}


void solve3(int arr[], int n) {
	int lis[n], firstDay, lastDay;
	lis[0] = 1;
	
	for(int i = 1; i<n; i++) {
		lis[i] = 1;
		for(int j = 0; j<i; j++) {
			if(arr[i] > arr[j] && lis[i] < lis[j] + 1)
				lis[i] = lis[j] + 1;
		}
	}
	
	int max = 0;
	int min = lis[0];
	firstDay = 1;
	for(int i = 0; i<n; i++) { 
		if(max < lis[i]) {
			max = lis[i];
			lastDay = i+1;		
		}
		if(min > lis[i]) {
			min = lis[i];
			firstDay = i+1;
		}
	}
	cout << "Longest spread period of " << max << " from day " << firstDay << " to day " << lastDay << endl << endl;
}


void case3(string &country) {
	Node *nodePtr = dataSet.head;
	int arr[256]; // To store the data for confirmed cases in a separate array.
	int counter = 0;
	bool condition = false;
	while(nodePtr) {
		if(nodePtr->name == country) {
			for(int i = 0; i<nodePtr->size; i++) {
				arr[counter] = nodePtr->confirmed[i];
				counter++;
				if(i == nodePtr->size-1)
					condition = true;
			}
		}
		nodePtr = nodePtr->next;
	}
	
	if(condition) {
		cout << country << " has ";
		solve3(arr,counter);
	}
	else
		return;
}

void solve4(int arr[], int n) {
	int lds[n];
	lds[0] = 1;
	
	for(int i = 1; i<n; i++) {
		lds[i] = 1;
		for(int j = 0; j<i; j++) {
			if(arr[i] < arr[j] && lds[i] < lds[j] + 1)
				lds[i] = lds[j] + 1;
		}
	}
	
	int max = 0;
	for(int i = 0; i<n; i++)
		if(max < lds[i]) 
		   max = lds[i];
	
	cout << "Longest daily death toll decrease period of " << max << endl << endl;
			
}

void case4(string &country) {
	Node *nodePtr = dataSet.head;
	int arr[256]; // To store the data for confirmed cases in a separate array.
	int counter = 0;
	bool condition = false;
	while(nodePtr) {
		if(nodePtr->name == country) {
			for(int i = 0; i<nodePtr->size; i++) {
				arr[counter] = nodePtr->deaths[i];
				counter++;
				if(i == nodePtr->size-1)
					condition = true;
			}
		}
		nodePtr = nodePtr->next;
	}
	
	if(condition) {
		cout << country << " has ";
		solve4(arr,counter);
	}
	else
		return;
}

int max(int x, int y) {
	if(x > y)
		return x;
	else
		return y;
}

void case5() {
	int cases[256];
	int weight[256];
	string country[256];
	int budget = 300;
	Node* nodePtr = dataSet.head;
	int counter = 0;

	while(nodePtr) {
		country[counter] = nodePtr->name;
		cases[counter] = nodePtr->cumulativeConfirmed[nodePtr->size-1];
		cases[counter] -= nodePtr->cumulativeDeaths[nodePtr->size-1];
		weight[counter] = nodePtr->score;
		counter++;
		nodePtr = nodePtr->next;		
	}
	
	int size = counter;
	
	int K[size+1][budget+1];
	
	for(int i = 0; i<=size; i++) {
		for(int w = 0; w<=budget; w++) {
			if(i == 0 || w == 0)
				K[i][w] = 0;
			else if(weight[i] <= w) 
				K[i][w] = max(cases[i] + K[i-1][w-weight[i]],K[i-1][w]);
			else
				K[i][w] = K[i-1][w];
		}
	}	
	
	int x = size , y = budget;
	cout << endl;

	while(x > 0 && y > 0) {
		if(K[x][y] == K[x-1][y]) {
			x--;
		}
		else {
			cout << country[x] << " is included with highest score = " << K[x][y] << endl;
			x--;
			y = y - weight[x];
		}
	}
	
	cout << endl;
}

int main() {
	fileRead();
	int choice;
	while(1) {	
	
		cout << "Case 1: Find top 20 countries with most confirmed cases." << endl;
		cout << "Case 2: Find the country(s) with highest new cases b/w two dates." << endl;
		cout << "Case 3: Find the longest spread period of the given country." << endl;
		cout << "Case 4: Find the longest daily death toll decrease period of the given country." << endl;
		cout << "Case 5: Find the highest score attainable along with countries given a budget of 300." << endl;
		cout << "To terminate the program, enter -1." << endl;
		cout << "Enter your choice: ";		
		cin >> choice;
		
		if(choice == 1) {		
			string date;			
			cout << "Enter date(YYYY-MM-DD): ";
			cin >> date;
			case1(date);
		}
		else if(choice == 2) {
			string sDate,eDate;
			cout << "Enter start date(YYYY-MM-DD): ";
			cin >> sDate;
			cout << "Enter end date(YYYY-MM-DD): ";
			cin >> eDate;
			case2(sDate,eDate);
		}
		else if(choice == 3) {
			cin.ignore();
			string country;
			cout << "Enter country name: ";
			getline(cin,country);
			case3(country);
		}
		else if(choice == 4) {
			cin.ignore();
			string country;
			cout << "Enter country name: ";
			getline(cin,country);
			case4(country);
		}
		else if(choice == 5) {
			cin.ignore();
			case5();
		}
		else if(choice == -1)
			break;
		else 
			cout << "Please enter correct option. Try again." << endl;
		
	}
}









