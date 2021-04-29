/* -------------------Assignment 2: Closest Pair of Points in C++ -------------------
Author: Sukriti Tiwari
-------------------------------------------------------------------------------

** Data structures used:
1. Structure to store x and y coordinates of a point

List of Classes: 
1. readdata: to read data from the file and store in an array of structures
2. calculateDistance: to calculate distance between points in the bar/strip close to the centre

Assumptions: 1. All point coordinates are of type double.
2. The first integer in the input file is the number of points
3. To prevent it from rounding off to nearest number in the comparator function, we are returning -1 if the value is too small.
4. 
*/

// -----------HEADER FILES--------------------
#include <limits>
#include <iostream> 
#include <float.h> 
#include <stdlib.h> 
#include <math.h> 
#include <fstream>
#include<bits/stdc++.h> 

using namespace std;

// Defines maximum number of points
#define MAX 10000


// ------------A structure to represent a Point in 2D plane-------------------
struct point
{ 
    double x, y; 
}; 


// ----------------------------------------CLASS "INPUTDATA" DEFINED---------------------------------
class inputdata
{
    //--------------------------MEMBER VARIABLES DEFINED---------------------------
    public:
    ifstream infile;
    int n;
    point P[MAX];
     

    //------------------------READ DATA FROM FILE-------------------------------
    void readdata()
    {

        infile.open("program2trivialdata.txt");

        //---------check if file opens or not-------------------
        if (infile.fail())
        {
            cout << "Error reading file!";
        }

        // -------------if file opens, start reading data--------------
        else
        {
            // read number of inputs
            infile >> n;                 

            for (int i = 0; i < n; i++)
            {
                //read point coordinates

                infile >> P[i].x >> P[i].y;               
            }
        }
    }
};

// -------------COMPARATOR FUNCTIONS----------------------------------------
//Pre-condition: Inputs coordinates by reference - hence "const" used
//Post-condition: Error handling based on invalid input. Returns -1 in case of negative value. 

// Array of points needs to be sorted according to X coordinate on 2D plane

int compareX(const void* a, const void* b) 
    { 
        point *p1 = (point *)a,  *p2 = (point *)b;
        if((p1->x - p2->x)<0){
            return -1;
        } else if((p1->x - p2->x)>0){
            return 1;
        } else{
            return 0;
        }
    } 
// Array of points needs to be sorted according to Y coordinate on 2D plane

    int compareY(const void* a, const void* b) 
    { 
        point *p1 = (point *)a,   *p2 = (point *)b; 
        if((p1->y - p2->y)<0){
            return -1;
        } else if((p1->y - p2->y)>0){
            return 1;
        } else{
            return 0;
        }
    }
//-----------------------------------------------------------------


// ----------------CLASS "CALCULATEDISTANCE" DEFINED--------------------
//------- publically inherited from inputdata to handle scope---------------

class calculateDistance : public inputdata
{   
    public:  
    
    // A utility function to find the distance between two points using Euclidian distance
    //Pre-condition: Input pointer to points
    //Post-condition: returns the float type euclidian distance between points 

    float distance(point p1, point p2) 
    { 
        return sqrt( (p1.x - p2.x)*(p1.x - p2.x) + 
                    (p1.y - p2.y)*(p1.y - p2.y) 
                ); 
    } 

    // A Brute Force method to return the smallest distance between two points in P[] of size n 
    //Pre-condition: Input array of points and their size
    //Post-condition: Returns the smallest distance between points

    float smallestDistance(point P[], int n) 
    { 
        float min = numeric_limits<float>::max();
        float temp;
        int posi,posj,i,j;    // to get indices of points
        for ( i = 0; i < n; ++i) 
            for ( j = i+1; j < n; ++j)
                temp = distance(P[i], P[j]);
                if (temp < min){
                    posi=i;
                    posj=j;
                    min = temp;
                }

        return min; 
    } 
    
    // Function to find a minimum of two float distances 
    //Pre-condition: Inputs distances
    //Post-conditions: returns minimum distance

    float min(float x, float y) 
    { 
        return (x < y)? x : y; 
    } 
 

    /* Function to find the distance between the closest points of bar of a given size. All points in bar[] are sorted according to 
    y coordinate. They all have an upper bound on minimum distance as d. */
    //Pre-condition: Input taken as the set of points within distance d of middle partition
    //Post-condition: Returns the minimum distance between points withing the bar
 
    float barClosest(point bar[], int size, float d) 
    { 
        float min = d;    // Initialize the minimum distance as d 
    
        // Pick all points one by one and try the next points till the difference between y coordinates is smaller than d. 

        int posi, posj, i, j;
        for ( i = 0; i < size; ++i) 
            for ( j = i+1; j < size && (bar[j].y - bar[i].y) < min; ++j) 
                if (distance(bar[i],bar[j]) < min){
                    min = distance(bar[i], bar[j]);
                    posi=i;
                    posj=j;
                }
                    
        return min; 
    } 
    
    /* A recursive function to find the smallest distance. The array Px contains all points sorted according to x coordinates and Py contains all points 
      sorted according to y coordinates.
    Pre-condition: Input sorted array of x and y coordinates respe tively along with their size and indices */

    float closestRecursive(point Px[], point Py[], int n, int index) 
    { 
         double result;
        // If there are 2 or 3 points, then use brute force 
        if (n <= 3){
            result=smallestDistance(Px, n);
            display(result,index,n);
            return result;
        }

    
        // Find the middle point 
        int mid = n/2; 
        point midPoint = Px[mid]; 
    
    
        // Divide points in y sorted array around the vertical line. 
        // Assumption: All x coordinates are distinct. 

        point Pyl[mid];   // y sorted points on left of vertical line 
        point Pyr[n-mid];  // y sorted points on right of vertical line 
        int li = 0, ri = 0;  // indexes of left and right subarrays 
        for (int i = 0; i < n; i++) 
        { 
        if (Py[i].x <= midPoint.x && li<mid) 
            Pyl[li++] = Py[i]; 
        else
            Pyr[ri++] = Py[i]; 
        } 
    
        // Consider the vertical line passing through the middle point 
        // calculate the smallest distance leftdist on left of middle point and 
        // rightdist on right side 
        float leftdist = closestRecursive(Px, Pyl, mid, index); 
        float rightdist = closestRecursive(Px + mid, Pyr, n-mid,index+mid); 
    
        // Find the smaller of the two distances 
        float d = min(leftdist, rightdist); 
    
        // Build an array bar[] that contains points closer than d
        // to the line passing through the middle point 
        point bar[n]; 
        int j = 0; 
        for (int i = 0; i < n; i++) 
            if (abs(Py[i].x - midPoint.x) < d) 
                bar[j] = Py[i], j++; 
    
        // Find the closest points in bar.  Return the minimum of d and closest 
        // distance is bar[] 
        result= barClosest(bar, j, d);
        display(result,index,n);
        return result;
    } 
    

    // Function that finds the smallest distance overall
    // This method mainly uses closestRecursive() 
    float findclosestpoint(point P[], int n) 
    { 
        point Px[n]; 
        point Py[n]; 
        for (int i = 0; i < n; i++) 
        { 
            Px[i] = P[i]; 
            Py[i] = P[i]; 
        } 

        // Quick sort
        qsort(Px, n, sizeof(point), compareX); 
        qsort(Py, n, sizeof(point), compareY); 
    
        // Use recursive function closestRecursive() to find the smallest distance 
        return closestRecursive(Px, Py, n, 0); 
    } 

    // Function to display final output after each recursive call
    void display(double result,int start,int end)
    {
        cout<<"D["<<start<<","<<start+(end-1)<<"]: "<<fixed<<setprecision(4)<<result<<"\n";
    }

  

};


// -----------------------------------MAIN--------------------------------------------
int main() 
{ 
    inputdata read;
    calculateDistance c1;

    read.readdata();
    c1.findclosestpoint(read.P, read.n); 
    return 0; 

    //--------------------end of program----------------------------------------

} 

    