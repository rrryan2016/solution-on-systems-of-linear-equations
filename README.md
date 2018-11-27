# Basic project in Continuous system simulation
###Program 1 - Data Interpolation 

* Lagrange Interpolation;
* Newton Interpolation;
* If you want to use your own data, please ensure the data layout in *input.txt* and *testx.txt* is same to the original file;
* Ensure all the file below are in the same path;
* Detailed annotations are in the file.

|File Name|Application|
|:-:|:-:|
|main.cpp|main program to run|
|input.txt|Given Data|
|testx.txt|Data X to calculate|
|Result.txt|Result saved in this file(show after running)|

###程序1 - Data Interpolation 

* 拉格朗日插值法；
* 牛顿插值法；
* 如果你想使用你自己的数据，请确保数据输入及存储的格式同原始的input.txt和testx.txt是一致的；
* 请确保以下的文件均放在同一个文件夹之下；
* 更细节的注释在文档中。

|文件名|含义|
|:-:|:-:|
|main.cpp|待运行的主程序|
|input.txt|已知的数据对|
|testx.txt|待求的数据|
|Result.txt|存储结果的文件（主程序运行之后才会出现）|

### Program 2 - Data Fitting
* Using least square method to do data fitting, includings the solution of linear equation by Newton Elimination Method and LU Decomposition Method.

1. Solution of linear equation 
> Transfer the equations into augmented matrix.
> 1.1 Gaussian Elimination Method
> The whole process divided into 2 parts, elimination and inverse calculayion. 
> Actually, it transfer the augmented matrix into upper triangular matrix and then, do iteration from the bottom to the upper. 
> 1.2 LU Decomposition Method
> On the basis of gaussian elimination, its idea is to divide the augmented matrix into 2 triangular matrixes. The detaled LU Decomposition formula please check other sources. 
2. Least Sqaure Method 
> The fitted degree of a polynomal can be and must be assigned by the user in the window when the program is running. For example,
> When $degree=2$, $$y = a_0+a_1x+a_2x^2$$
> When $degree=3$, $$y = a_0+a_1x+a_2x^2+a_3x^3$$
> When $degree=4$, $$y = a_0+a_1x+a_2x^2+a_3x^3+a_4x^4$$
> Be attention that the assigned term cannot be bigger than the amount ot data you give.
> 

* The detailed results are saved in the file, named *computation_sheet.txt*,including the degree of fitting polynomial you assigned, exact fitted polymonial and calculated data. 
* If you want to use your own data, please ensure the data layout in *rawData.txt* and *x2Calculate.txt* is same to the original file. For example, line 1 in *rawData.txt* is data x, and line 2 is data y, while there is only one line in *x2Calculate.txt*.

|File Name |Application|
|:-:|:-:|
|fitting.cpp|main program to run|
|rawData.txt|Given Data|
|x2Calculate.txt|Data X to calculate|
|computation_sheet.txt|Result saved in this file(show after running)|

PS. The develop environment is Windows 7 + Visual Studio 2017