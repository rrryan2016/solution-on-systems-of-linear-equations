#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

// Display a linear array
void arrayDisplay(double* ex, int sum)//To show a vector
{
	for (int i = 0; i < sum; i++)
	{
		cout << ex[i] << " ";
	}
}

// Display a matrix 
void matrixDisplay(double** sample, int row, int col)//To show a matrix
{
	for (int i = 0; i < row; i++)
	{
		arrayDisplay(sample[i], col);
		cout << endl;
	}
	cout << endl;
}

// 
void gause_elimination(double **augmentedMatrix, double *coefficient,int n)//Gause Elimination Method
{
	//Elimination process  消元过程
	double lamda;
	for (int i = 0; i < n; i++)// Calculation proceeds to the i th line 计算到了第i行，对角线上第i个
	{
		for (int j = i + 1; j < n; j++)// At each line, all j(after i) will minus later   i 后面的每一行都会操作被减
		{
			lamda = augmentedMatrix[j][i] / augmentedMatrix[i][i];//Figure out the lambda 确定系数
			for (int k = i; k < n + 1; k++)	//Process on each after line j 对第j行之后的每一位操作
			{
				augmentedMatrix[j][k] = augmentedMatrix[j][k] - lamda * augmentedMatrix[i][k];
			}
		}
	}

	double* result = new double[n];
	double tempSum = 0;

	//Inverse Calculation 反向过程
	for (int i = n - 1; i > 0 || i == 0; i--)//Calculate per line, from bottom to the upper 逐行计算
	{
		for (int k = n - 1; k > i; k--)// Calculate the number to minus later 减去后面的项
		{
			tempSum += augmentedMatrix[i][k] * result[k];
		}
		augmentedMatrix[i][n] -= tempSum;
		result[i] = augmentedMatrix[i][n] / augmentedMatrix[i][i];
		tempSum = 0;
	}
	// Store in result into array named coefficient 
	//将结果放入供之后计算的系数参数数组
	for (int i = 0; i < n; i++)
	{
		coefficient[i] = result[i];
	}
}


 void LU_Decomposition(double **augmentedMatrix,double *coefficient,int n) //LU Decomposition Method
 {
 	//Establishment of L U Y X 
 	//首先为LUYX四个必要的矩阵/向量开辟空间
	 double** L = new double *[n];
	 for (int i = 0; i < n; i++)
	 {
		 L[i] = new double[n];
	 }
	 double** U = new double *[n];
	 for (int i = 0; i < n; i++)
	 {
		 U[i] = new double[n];
	 }
	 double* Y = new double[n];
	 double* X = new double[n];

	 //Initialization OF L & U 
	 //LU矩阵的初始化 三角矩阵可以提前填0 或者 在对角线上填1
	 for (int i = 0; i < n; i++)
	 {
		 for (int j = 0; j < n; j++)
		 {
			 U[i][j] = 0;
			 if (i == j) { L[i][j] = 1; }
			 else { L[i][j] = 0; }
		 }
	 }

	 // LU Decomposition (Detailed mechnism please check other sources)
	 // LU矩阵的搭建计算过程
	 double tempSum = 0;
	 for (int k = 0; k < n - 1; k++)
	 {
		 if (k == 0)
		 {
			 for (int j = 0; j < n; j++)
			 {
				 U[0][j] = augmentedMatrix[0][j];
			 }
			 for (int i = 1; i < n; i++)
			 {
				 L[i][0] = augmentedMatrix[i][0] / augmentedMatrix[0][0];
			 }
		 }
		 else {
			 for (int j = k; j < n; j++)
			 {
				 for (int r = 0; r < k; r++)
				 {
					 tempSum += L[k][r] * U[r][j];
				 }
				 U[k][j] = augmentedMatrix[k][j] - tempSum;
				 tempSum = 0;
			 }
			 for (int i = k + 1; i < n; i++)
			 {
				 for (int r = 0; r < k; r++)
				 {
					 tempSum += L[i][r] * U[r][k];
				 }
				 L[i][k] = (augmentedMatrix[i][k] - tempSum) / U[k][k];//
				 tempSum = 0;
			 }
		 }
	 }

	 //Calculate the last term in U (algorithm regulated)
	 //单独计算U的最后一项，最右下角一项
	 for (int r = 0; r < n - 1; r++)
	 {
		 tempSum += L[n - 1][r] * U[r][n - 1];
	 }
	 U[n - 1][n - 1] = augmentedMatrix[n - 1][n - 1] - tempSum;
	 tempSum = 0;

	 //Calculate Y 
	 //计算Y向量
	 for (int i = 0; i < n; i++)
	 {
		 if (i == 0)// Due to the upper triangular matrix, we calculate from upper to the bottom 因为是上三角矩阵，所以从上往下计算
		 {
			 Y[i] = augmentedMatrix[0][n];
		 }
		 else
		 {
			 for (int j = 0; j < i; j++)
			 {
				 tempSum += L[i][j] * Y[j];

			 }
			 Y[i] = augmentedMatrix[i][n] - tempSum;
			 tempSum = 0;
		 }
	 }

	 //Claculate X 
	 //计算X向量
	 for (int i = n - 1; i > 0 || i == 0; i--)
	 {
		 if (i == n - 1) //Due to lower triangular matrix, we calculate from bottom to the upper. 因为是下三角矩阵，所以从下往上计算
		 	{ X[n - 1] = Y[n - 1] / U[n - 1][n - 1]; }
		 else
		 {
			 for (int j = i + 1; j < n; j++)
			 {
				 tempSum += U[i][j] * X[j];
			 }
			 X[i] = (Y[i] - tempSum) / U[i][i];
			 tempSum = 0;
		 }
	 }
	 // Store in result into array named coefficient 
	 //将结果放入供之后计算的系数参数数组
	for (int i = 0; i < n; i++)
	{
		coefficient[i] = X[i];
	}
 }
// Calcualte polynomial (assuming we know every coefficient)
//多项式计算函数（已知各项系数）
double polynomial_Calculation(double* coefficient,int m, double x)
{
	double ans = 0;
	for(int i=0;i<m+1;i++)
	{
		ans += coefficient[i]*pow(x,i);
	}
	return ans;
}

int main()
{
	//Count the size of the input
	fstream in1("rawData.txt",ios::in);
	double c;
	int sum = 0;
	while(in1>>c)sum++;
	in1.close();

	int dataLength = sum / 2; // the number of known point 
	int n = dataLength - 1;//According to the state in book 
	double* x_data = new double[dataLength]; //size=n+1 0,...,n
	double* y_data = new double[dataLength]; //size=n+1 0,...,n

	cout<<endl << "Loading the raw data..." << endl;
	//Load x_data & y_data
	ifstream in2("rawData.txt");
	for(int i=0 ; i<dataLength;i++)
	{
		in2>>x_data[i];
	}
	for(int i = dataLength;i<sum;i++)
	{
		in2>>y_data[i-dataLength];

	}
	in2.close();
	
	// Note assigned term of polynomial by user
	//输入用户期待的拟合的次数
	int m;
	cout <<endl<< "Please tell me the degree of your expected polynomial:	";
	cin >> m;
	while (m > n)
	{
		cout << "Please ensure the degree of polynomial is less than or equal to the number of known points";
		cin >> m;
	}

	//Set up the Augmented Matrix 
	double** augmentedMatrix = new double*[m + 1];
	for (int i=0; i<m+1;i++)
	{
		augmentedMatrix[i] = new double [m+2];
	}
	// augmentedMatrix can be divided into 2 parts, s & t
	//s refers to augmentedMatrix[0:m][0:m-1]
	//t refers to augmentedMatatrix[0:m][m]

	double tempMulti =1 ;
	double tempSum = 0;
	cout << endl << "Calculating the augmented matrix ... " << endl;
	//Calculate the s
	for(int j=0;j<m+1;j++)
	{
		for(int k=0;k<m+1;k++)
		{
			for(int i=0;i<n+1;i++)
			{
				tempSum += pow(x_data[i],j+k);
			}
			augmentedMatrix[j][k]= tempSum;
			tempSum = 0;
		}
	}

	//Calculate the t
	for(int j = 0 ; j<m+1 ;j++)
	{
		for(int i = 0; i<n+1;i++)
		{
			tempSum += y_data[i]*pow(x_data[i],j);
		}
		augmentedMatrix[j][m+1] = tempSum;
		tempSum = 0;
	}
	//cout << "Augmented matrix: " << endl;
	//matrixDisplay(augmentedMatrix, m + 1, m + 2);
	double* coefficient = new double[m + 1];

	// You can use but can only use one of these two lines of codes below
	// gause_elimination(augmentedMatrix, coefficient,m+1);
	cout << endl << "Solving the augmented matrix ... " << endl;
	LU_Decomposition(augmentedMatrix,coefficient,m+1);

	cout<<endl<<"Display the coefficients of fitting polynomial(from low to high):"<<endl;
	arrayDisplay(coefficient, m + 1);
	cout <<endl<<endl;



	// Count the amount of data to calculate 
	//统计待求的项数 
	fstream in4("x2Calculate.txt",ios::in);
	double d;
	int x_sum = 0;
	while(in4>>d)x_sum++;
	in4.close();

	double* x2Calculate = new double[x_sum];
	// Load array to calculate, saving data x 
	//读入
	fstream in5("x2Calculate.txt",ios::in);
	for(int i=0;i<x_sum;i++){
		in5>>x2Calculate[i];
	}

	// Calculation and saving into TXT file 
	//计算并且写入TXT文档
	cout << "Saving the final computation result ..." << endl;
	ofstream finalfile("computation_sheet.txt", ios::out);
	if (!finalfile) {
		cout << "Error! Failed to write the result into TXT file." << endl;
	}
	else {
		finalfile<<"The degree of fitting polynomial is "<<m<<endl;
		finalfile<<"f(x) = ";
		for (int i=0;i<m+1;i++)
		{
			if(i==0)
			{
				finalfile<<coefficient[i]<<" ";
			}
			else
			{
				if(coefficient[i]<0);
				else{finalfile<<"+";}
				finalfile<<coefficient[i]<<"x^"<<i<<" ";
			}

		}
		finalfile<<endl;
		for(int i=0;i<x_sum;i++)
		{
			finalfile<<"X"<<i+1<<" = "<<x2Calculate[i]<<"	Y"<<i+1<<" = "<<polynomial_Calculation(coefficient,m,x2Calculate[i])<<endl;
		}
	}
	finalfile.close();

	cout <<endl<< "Congratulate! All done!" << endl;

	//Window Control 
	int end = 0;
	while(end!=1)
	{
		cin>>end;
	}
}

