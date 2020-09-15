#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    double s[3]; //summa B, G, R po odnoy stroke
    double t[3]; //summa B, G. R po vsemu izobrajeniu
    int flag = 0; //schotchik "ne sylno otlichayuschiksya" pikseley v stroke
    bool flag_1 = false; //nalichie stroki, sostoyaschey iz fona
    Mat img = imread("test4.jpg");

    for (int k = 0; k < 3; k++) {
        t[k] = 0;
    }

    for (int i = 0; (i < img.rows) && (flag != img.cols - 1); i++) {
        flag = 0;

        for (int k = 0; k < 3; k++) {
            s[k] = 0;
        }

        for (int j = 0; (j < img.cols - 1) && (flag != img.cols - 1); j++) {


            if (((double)img.at<Vec3b>(i, j)[0] < (double)img.at<Vec3b>(i, j + 1)[0] + 50) && //uslovie togo, chto v stroke net pikseley teksta
                ((double)img.at<Vec3b>(i, j)[1] < (double)img.at<Vec3b>(i, j + 1)[1] + 50) &&
                ((double)img.at<Vec3b>(i, j)[2] < (double)img.at<Vec3b>(i, j + 1)[2] + 50)) {
                flag = flag + 1;
                for (int k = 0; k < 3; k++) {

                    s[k] = s[k] + (double)img.at<Vec3b>(i, j)[k];

                }
            }
            else {

                flag = 0;
                break;
            }
        }
    }
    if (flag == 0) {
        for (int i = 0; (i < img.rows); i++) {
            for (int j = 0; j < img.cols; j++) {
                for (int k = 0; k < 3; k++) {

                    t[k] = t[k] + (double)img.at<Vec3b>(i, j)[k];

                }
            }
        }
        for (int k = 0; k < 3; k++) {
            if (t[k] / (img.cols * img.rows) > 127.5) {
                cout << "Light background" << endl;
                flag_1 = true;
                break;
            }

        }

    }
    else {
        for (int k = 0; k < 3; k++) {
            if (s[k] / (img.cols - 1) > 127.5) {
                cout << "Light background" << endl;
                flag_1 = true;
                break;
            }
        }
    }

    if (!flag_1) {
        cout << "Dark background" << endl;
    }

    imshow("Display Window", img);
    waitKey(0);
    return 0;
}

