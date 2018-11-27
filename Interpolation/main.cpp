#include <fstream>
#include <string>
#include <iostream>
using namespace std;

// Function to show an array
void arrayDisplay(double* ex ,int sum)
{
	for (int i = 0; i < sum; i++)
	{
		cout << ex[i] << endl;
	}
}

int main()
{
	cout<<"Calculating Data Value ... "<<endl;
	//Get the amount of the inputed data, in order to set up dynamic matrix later. 
	int sum = 0;
	ifstream in1("input.txt");
	string s;
	while (getline(in1, s))
	{
		sum++;
	}
	in1.close();

	//Set up the dynamic matrix to store the inputed data
	int sumOfResult = 0;
	ifstream in2("testx.txt");
	while (getline(in2, s))
	{
		sumOfResult++;
	}
	in2.close();

	cout << "Inputing Data  ... " << endl;
	// Set up 2 linear arrays 
	double* x_data = new double[sum];
	double* y_data = new double[sum];
	// Load the data into 2 arrays
	ifstream infile("input.txt");
	for (int i = 0; i < sum; i++)
	{
		infile >> x_data[i];
		infile >> y_data[i];
	}
	infile.close();

	//Set up arrays to load data to calculate & save claculated data. 
	double* x_test = new double[sumOfResult];
	double* y_lagrange = new double[sumOfResult];
	double* y_newton = new double[sumOfResult];
	// Load data to calculate 
	ifstream infile1("testx.txt");
	for (int i = 0; i < sumOfResult; i++)
	{
		infile1 >> x_test[i];
		y_lagrange[i] = 0;
		y_newton[i] = 0;
	}
	infile1.close();

	cout << "Calculating Lagrange Interpolation ... " << endl;
	//Process of Lagrange Interpolation
	double* term = new double[sum];//Ã¿Ò»Ïî
	for (int i = 0; i < sumOfResult; i++)
	{ 
		for (int j = 0; j < sum; j++)
		{
			term[j] = y_data[j];
			for (int k = 0; k < sum; k++)
			{
				if (j != k)
				{
					term[j] *= (x_test[i] - x_data[k]) / (x_data[j] - x_data[k]);
				}
			}
			y_lagrange[i] += term[j];
		}
	}

	cout << "Calculating Newton Interpolation ... " << endl;
	//Process of Newton Interpolation
	double **Term = new double*[sum];
	for (int i = 0; i < sum; i++)
	{
		Term[i] = new double[sum];
	}

	for (int i = 0; i < sum; i++)
	{
		Term[i][0] = y_data[i];
		for (int j = 1; (j < i) || (j == i); j++)
		{
			Term[i][j] = (Term[i][j - 1] - Term[i - 1][j - 1]) / (x_data[i] - x_data[i - j]);
		}
	}

	double error;
	for (int k = 0; k < sumOfResult; k++)
	{
		for (int i = 0; i < sum; i++)
		{
			error = Term[i][i];
			for (int n = 0; n < i; n++)
			{
				error *= (x_test[k] - x_data[n]);
			}
			y_newton[k] += error;
		}
	}

	cout << "Outputing Interpolation Result to TXT File ... " << endl;
	ofstream outfile("Result.txt", ios::out);
	if (!outfile) { cout << "ERROR!!" << endl; }
	else
	{
		outfile << " x_test			y_lagrange			y_newton " << endl;
		for (int i = 0; i < sumOfResult; i++)
		{
			outfile << x_test[i] << "			" << y_lagrange[i] << "			" << y_newton[i] << endl;
		}
	}

	cout << "Finished !" << endl;

	//window control 
	int end = 0;
	while (end != 1)
	{
		cin >> end;
	}
	return 0; 
}

