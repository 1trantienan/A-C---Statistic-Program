#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <math.h>


using namespace std;


//function to find median
double findMedian(int arr[], int len)
{
     // Sort the array
    for (int i = 0; i < len; ++i)    
    {
        for (int j = i + 1; j < len; ++j)
        {
            if (arr[i] > arr[j])
            {
                int temp =  arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
 
    if (len % 2 != 0)  // check for even case
    {
        return (double)arr[len / 2]; // formula for calculating median value
    }
    else  // check for odd case
    {
    return (double)(arr[(len - 1) / 2] + arr[len / 2]) / 2.0; // formula for calculating median value
}
}

//function to find mean
double findMean(int arr[], int len)
{
    double sum = 0;
    for (int i = 0; i < len; i++)
    {
        sum = sum + arr[i]; //calculate sum of values
    }
    double avg = sum / len; //find mean
    return avg;
}

//function to find mode
double findMode( int arr[], int len){
    
    //sort(arr, arr + len);   
  
    int max_count = 1, res = arr[0], count = 1; //finding max frequency 
    for (int i = 1; i < len; i++) { 
        if (arr[i] == arr[i - 1]) 
            count++; 
        else { 
            if (count > max_count) { 
                max_count = count; 
                res = arr[i - 1]; 
            } 
            count = 1; 
        } 
    } 
    
    if (count > max_count)  // when the last element is most frequent 
    { 
        max_count = count; 
        res = arr[len - 1]; 
    } 
    
    return res;
}

// function to calculate standard deviation
double findVariance(int arr[], int len) 
{
    double sum = 0.0, mean, sd = 0.0;
	mean = findMean(arr, len); // find mean.
    for(int i = 0; i < len; ++i)
        sd = sd + pow(arr[i] - mean, 2); // calculating standard deviation
    //cout << "Variance_X = " << sd / len << "OOOOOOOOOO\n";
    return sd / len;
}

//finction to calcuate mean absoulute deviation
double meanAbsoluteDeviation(int arr[], int len)
{  
    double sum_mad = 0;
    for (int i = 0; i < len; i++)
    {
    	int mean = findMean(arr, len); //find mean
        sum_mad = sum_mad + abs(arr[i] - mean);  //formula for calculating mean absoulute deviation
}
    
    return sum_mad / len; 
}

// Function to calculate index for finding Quartile 3
int index( int end, int start)
{
	int n = end - start + 1;
	n = (n + 1) / 2 - 1;
	return n + start;
}

// Function to calculate Quartile 3
int findQuartile(int arr[], int len)
{
	// Sort the array
	for (int i = 0; i < len; ++i)    
    {
        for (int j = i + 1; j < len; ++j)
        {
            if (arr[i] > arr[j])
            {
                int temp =  arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

	int mid_index = index(0, len);  // Index of median of entire data
    
	int Q3 = arr[index( mid_index + 1, len)]; // Quartile 3 calculation
    
	return (Q3);
}
 
double findSkewness(int arr[], int len)
{
	// Find skewness using above formula
	double sum = 0;
	double mean = findMean(arr, len);  //find mean
	for (int i = 0; i < len; i++)
	{
		sum = sum + pow((arr[i] - mean),3) ;   //sum of difference of values from its mean
    }
	double stdev = sqrt (findVariance(arr, len));	 //stdev calculation 
	
	return sum / ((len-1)* pow( stdev ,3));        //formula for calculating skewness
}

//function to find covariance
double findKurtosis(int arr[], int len)
{
	double sum = 0;
	double mean = findMean(arr, len);  //find mean 
	for (int i = 0; i < len; i++)
	{
		sum = sum + pow((arr[i] - mean),4) ; //sum of difference of values from its mean
    }
	double stdev = sqrt (findVariance(arr, len));	 //stdev calculation 
	
	//formula for calculating kurtosis
	double ans = sum / ((len-1)* pow( stdev ,4)); 
	return ans -3;
}

// Function to find covariance.
double findCovariance(int x[], int y[], int len)
{
	double sum = 0;
	for(int i = 0; i < len; i++)
	{
		sum = sum + (x[i] - findMean(x, len)) * (y[i] - findMean(y, len)); //formulate for calculating covariance
}
	return sum / (len - 1);
}

//function to find correlation coefficient
double correlationCoefficient(int X[], int Y[], int len)
{

	int sum_X = 0, sum_Y = 0, sum_XY = 0;
	int squareSum_X = 0, squareSum_Y = 0;

	for (int i = 0; i < len; i++)
	{
		// sum of elements of array X.
		sum_X = sum_X + X[i];

		// sum of elements of array Y.
		sum_Y = sum_Y + Y[i];

		// sum of X[i] * Y[i].
		sum_XY = sum_XY + X[i] * Y[i];

		// sum of square of array elements.
		squareSum_X = squareSum_X + X[i] * X[i];
		squareSum_Y = squareSum_Y + Y[i] * Y[i];
	}

	// use formula for calculating correlation coefficient.
	double corr = (len * sum_XY - sum_X * sum_Y)
				/ sqrt((len * squareSum_X - pow(sum_X, 2))
					* (len * squareSum_Y - pow(sum_Y, 2)));

	return corr;
}

//function to find linear regression line
void linearRegression(int x[], int y[], int len)
{
       double a = 	(correlationCoefficient(x, y, len) * sqrt(findVariance(y, len)))/sqrt(findVariance(x, len)); //use formula for calculating the value of a
       double b = findMean(y, len) - a*findMean(x, len); // use formula for calculating the value of b
       
       cout << a << "X + " << b << endl; 
}


int main()
{
	int count = 0;				//total number of line
	int x[50001], y[50001];		//initializatiion of arrays
	
	
	ifstream (fr);
	fr.open("data1.csv");		//read file
    if (fr.is_open()) 			//to check if file is open correctly or not
    {
	std::string str;			//skip the file header 
    std::getline(fr, str);
	while(fr.good())			
	{
		string value_x, value_y;		//variable to store file extracted value
		bool skip_x = true;				//exceptions for empty cell
		bool skip_y = true; 
		
		getline (fr,value_x,',');		//data extraction
		if (!value_x.empty())
		{   
	     	int X=stoi(value_x); //convert variable into integer
		    x[count]= X;					//store in array
		
	     }
	    else if (value_x.empty() && skip_x ) 
	    {
		    skip_x = false; //Skip the empty row/value/cell
	    } 
	        skip_x = true;
	    
		getline (fr,value_y,'\n');
		if (!value_y.empty())
		{
		  int Y=stoi(value_y);
	      y[count]= Y;
	    }
	    else if (value_y.empty() && skip_y ) 
	    {
		    skip_y = false; //Skip the empty row/value/cell
	    } 
	        skip_y = true;
		
		count++;
				
	}
	
	
	cout << "						Descriptive Statistics					" << endl << endl << endl;
	
	
	int len = sizeof(x) / sizeof(x[0]);   //calculate the length
	
	std::cout << std::fixed;
    std::cout << std::setprecision(4);
		
	cout << "Median_X = " << findMedian(x, len) << " - " << "Median_Y = " << findMedian(y, len) << endl << endl;
	cout << "Mean_X = " << findMean(x, len) << " - "  << "Mean_Y = " << findMean(y, len) << endl << endl;
	cout << "Mode_X = " << findMode(x, len) << " - " << "Mode_Y = " << findMode(y, len) << endl << endl;
	cout << "Variance_X = " << findVariance(x, len) << " - " << "Variance_Y = " << findVariance(y, len) << endl << endl;
	cout << "Stdev_X = " << sqrt (findVariance(x, len))<< " - " << "Stdev_Y = " << sqrt(findVariance(y, len))<< endl << endl;
	cout << "mad_X = " << meanAbsoluteDeviation(x, len) << " - " << "mad_Y = " << meanAbsoluteDeviation(y, len)<< endl << endl;
	cout << "Q3_X = " << findQuartile(x, len) << " - " << "Q3_Y = " << findQuartile(y, len)<< endl << endl;
	cout << "Skew_X = " << findSkewness(x, len) << " - " << "Skew_Y = " << findSkewness(y, len)<< endl << endl;
	cout << "Kurt_X = " << findKurtosis(x, len) << " - " << "Kurt_Y = " << findKurtosis(y, len)<< endl << endl;
	
	cout << "						Inferential Statistics					" << endl << endl << endl;
	
	cout << "cov(x_y) = " << findCovariance(x, y, len) << endl << endl;
	cout << "r(x_y) = " << correlationCoefficient(x, y, len) << endl << endl;
    cout << "Equation of Linear Regression: Y = ";
    linearRegression(x, y, len);
    cout << endl;
//detail of our team member
    cout << "Assignment 1 Group 18" << endl << endl;
	cout << "s3701522, s3701522@rmit.edu.vn, Pham, Nguyen Vu" << endl;
	cout << "s3795683, s3795683@rmit.edu.vn, Tran, Viet Anh" << endl;
	cout << "s3699000, s3699000@rmit.edu.vn, Tran, Tien An" << endl;
	cout << "s3741280, s3741280@rmit.edu.vn, Nguyen, Minh Duong" << endl;
}
else
{
	cout << "File Couldn't Open";
}
}
