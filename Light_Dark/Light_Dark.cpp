#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int findmax__index(int* arr, int sizeof_arr) {  //finds the index of the maximum element
    int max = arr[0];
    int index_max = 0;
    for (int i = 0; i < sizeof_arr; i++) {
        if (arr[i] > max) {
            max = arr[i];
            index_max = i;
        }      
    }
    return index_max;
}

void gist_create(Mat img, int* gist) {        //writes the brightness histogram to the given array
    double s = 0;
    int index = 0;
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            s = 0;
            for (int k = 0; k < 3; k++) {
                s = s + (double)img.at<Vec3b>(i, j)[k];
            }
            index = (int)(s / 3);
            gist[index] = gist[index] + 1;
        }
    }
}


int main()
{

    int gist[256]; //array for the future histogram
    
    for (int k = 0; k < 256; k++) {
        gist[k] = 0;
    }
    
    Mat img = imread("../test1.jpg");
    
    if (img.empty())
    {
        cout << "ERROR" << endl;
        return -1;
    }

    gist_create(img, gist);

    int index = findmax__index(gist, 256);  //finding the peak
    int i = index, j = index;
    int max = gist[index];
    int sum_right = 0, sum_left = 0;        

    while ((gist[i] >= max / 2) && (i < 256)) { 
        i = i + 1;
    }

    while ((gist[j] >= max / 2) && (j >= 0)) {
        j = j - 1;
    }

    for (int k = (2 * j - index); k < 256; k++)
        sum_right = sum_right + gist[k];

    for (int k = (2 * i - index); k >= 0; k--)
        sum_left = sum_left + gist[k];

    if (sum_right > sum_left)
        cout << "Dark background" << endl;
    else
        cout << "Light background" << endl;
    
   
    imshow("Display Window", img);
    waitKey(0);
    
    return 0;
}

