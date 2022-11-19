#include<iostream>
#include<fstream>
#include<string>
#include <iomanip>
#include <sstream>

using namespace std;

double Total_Lane_Queue_Time;

struct QueueCustomer {
	int items;
	string Prefered_Packaging;
	int Number_Packaging;
	string Prefered_Payment;
	string Cash_type;
};

QueueCustomer getData(string line)
{
	
	//Parse Data line, using [space] as delimiter
	
	size_t pos = 0;
	size_t npos = -1;
	string delimiter = " ";
	string data[5] = {""};
	int data_index = 0;
	
	while ((pos = line.find(delimiter)) != npos) {
	    data[data_index] = line.substr(0, pos);
	    line.erase(0, pos + delimiter.length());
	    data_index++;
	}
	data[data_index] = line;
	
	// set QueueCustomer data
	
	stringstream ss;
	
	QueueCustomer temp;
	
	for (int i = 0; i < 5; i++) {
		string d = *(data + i);
		if (i == 0 || i == 2) {
			ss << d;
			if (i == 0) {
				ss >> temp.items;
			} else if (i == 2) {
				ss >> temp.Number_Packaging;
			}
			ss.clear();
			ss.str("");
		} else if (i == 1) {
			temp.Prefered_Packaging = d;
		} else if (i == 3) {
			temp.Prefered_Payment = d;
		} else if (i == 4) {
			temp.Cash_type = d;
		}
	}
	return temp;
}

void Calculate_and_Display_Input(QueueCustomer n, int index)
{
	
	float Total_Decarting_Time;
	float Total_Scanning_Time;
	float Total_Packing_Time;
	float Total_Paying_Time;
	float Total_Reciept_Printing_Time;
	int Idle_Time;
	float Total_Customer_Queue_Time;
	
	
	int Customer_Number;

	//Display the Data
	
	Customer_Number = index + 1;
	
	cout << "Customer #" << Customer_Number << endl;
	cout << "No. of Cart Items: " << n.items << endl;
	cout << "Preferred Packaging: " << n.Prefered_Packaging << endl;
	cout << "Number of Packaging: " << n.Number_Packaging << endl;
	
	if(n.Cash_type == "e"){
		cout << "Preferred Payment Method: " << n.Prefered_Payment << " (exact) " << endl;
	}
	else if(n.Cash_type == "ne"){
		cout << "Preferred Payment Method: " << n.Prefered_Payment << " (not exact) " << endl;
	}
	else {
		cout << "Preferred Payment Method: " << n.Prefered_Payment << endl;
	}
	
	cout << "------------------------------------------------\n";
		 
	//Computes and Displays the Total Decarting Time 
	Total_Decarting_Time = n.items * 0.5;
	cout << "Total De-Carting Time: " << n.items << " * 0.5 = " << Total_Decarting_Time << endl;
	
	//Computes and Displays the Total Scanning Time
	Total_Scanning_Time =  n.items * 0.5;
	cout << "Total Scanning Time: " << n.items << " * 0.5 = " << Total_Scanning_Time << endl;
	
	//Determines the Prefered Packaging
	//Computes and Displays the Total Packing Time
	if(n.Prefered_Packaging == "box"){
		Total_Packing_Time = (n.items * 0.50) + (n.Number_Packaging * 10);
		cout << "Total Packing Time: (" << n.items << " * 0.5) + (" << n.Number_Packaging << " * 10) = " << Total_Packing_Time << endl;
	} 
	else if (n.Prefered_Packaging == "bag") {
		Total_Packing_Time = (n.items * 0.50) + (n.Number_Packaging * 5);
		cout << "Total Packing Time: (" << n.items << " * 0.5) + (" << n.Number_Packaging << " * 5) = " << Total_Packing_Time << endl;
	}
	
	//Determines the Prefered Payment
	//If the Prefered Payment Method is Cash, Determines the whether exact or not exact payment
	//Displays The Total Paying Time
	if(n.Prefered_Payment == "cash"){
		if(n.Cash_type == "e"){
			Total_Paying_Time = 15;
			cout << "Total Paying Time: " << Total_Paying_Time << endl;
		}
		else if(n.Cash_type == "ne"){
			Total_Paying_Time = 20;
			cout << "Total Paying Time: " << Total_Paying_Time << endl;
		}
	}
	if(n.Prefered_Payment == "digital"){
		Total_Paying_Time = 15;
		cout << "Total Paying Time: " << Total_Paying_Time << endl;
	}
	
	//Computes and Display the Total Receipt Printing Time
	Total_Reciept_Printing_Time = (n.items * 0.3) + 2;
	cout << "Total Receipt Printing Time: (" << n.items << " * 0.5) + 2 = " << Total_Reciept_Printing_Time << endl;
	
	//Displays the Idle_Time
	if(index == 0){
		Idle_Time = 0;
		cout << "Idle Time: " <<  Idle_Time << endl;
	} else if(index > 0){
		Idle_Time = 3;
		cout << "Idle Time: " <<  Idle_Time << endl;
	}
	
	//Computes and Displays the Total Customer Queue Time
	Total_Customer_Queue_Time = Total_Decarting_Time + Total_Scanning_Time + Total_Packing_Time + Total_Paying_Time + Total_Reciept_Printing_Time + Idle_Time;
	cout << "Total Customer-Queue Time: " << Total_Customer_Queue_Time << endl;
	
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	
	// Computes the Total_Lane_Queue_Time
    Total_Lane_Queue_Time += Total_Customer_Queue_Time;

	  
		 
}


int main( )
{
	ifstream in_stream;
	
	// Open the input file
	
	in_stream.open("project.txt");
	
	if(in_stream.fail())
    {
        cout<<"Input file opening failed.\n";
        exit(1);
    } 
	
	// Reads the Number Of Customer
	
	int Number_Of_Customer;
	
	in_stream >> Number_Of_Customer;
	
	cout << "No. of Customers:: " << Number_Of_Customer << endl;
	cout << "================================================\n";
	
	QueueCustomer queue[Number_Of_Customer];
	
	QueueCustomer n;
		
	string line;
	
	int index = 0;
	
	// For each succeeding lines of strings...
	while (getline(in_stream, line)) {
		if (line.length() > 0) {
			// Parse data and store to list
			queue[index] = getData(line);
			// Calls out the fuction which Calculates and Displays the Output
			Calculate_and_Display_Input(queue[index],index);
			index++;
		}
	}
	
	// Computes the Total_Lane_Queue_Time
    cout << "Total Lane Queue Time: " << Total_Lane_Queue_Time;
	
	return 0;
}
