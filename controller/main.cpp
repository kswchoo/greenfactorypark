#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <curl/curl.h>
#include <iostream>

using namespace cv;
using namespace std;

void upload() {
    CURL *curl;
    CURLcode res;
    struct curl_httppost *formpost = NULL;
    struct curl_httppost *lastptr = NULL;

    curl_global_init(CURL_GLOBAL_ALL);
    curl_formadd(&formpost, &lastptr,
            CURLFORM_COPYNAME, "birdview",
            CURLFORM_FILE, "/tmp/birdview.jpg",
            CURLFORM_END);

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://sungwoo.me/greenfactorypark/upload.php");
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);

        /* then cleanup the formpost chain */
        curl_formfree(formpost);
        /* free slist */
    }
}

int main(int argc, char *argv[]) {
    VideoCapture cap(0); // open the video camera no. 0
    if (!cap.isOpened())  // if not success, exit program
    {
        cout << "Cannot open the video cam" << endl;
        return -1;
    }

    double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
    double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

    cout << "Frame size : " << dWidth << " x " << dHeight << endl;

    Point2f inputQuad[4], outputQuad[4];
    inputQuad[0] = Point2f(250, 57);
    inputQuad[1] = Point2f(571, 136);
    inputQuad[2] = Point2f(244, 462);
    inputQuad[3] = Point2f(-143, 214);

    outputQuad[0] = Point2f(50, 70);
    outputQuad[1] = Point2f(dWidth - 130, 70);
    outputQuad[2] = Point2f(dWidth - 130, dHeight - 80);
    outputQuad[3] = Point2f(50, dHeight - 80);
    Mat lambda(2, 4, CV_32FC1);
    lambda = getPerspectiveTransform(inputQuad, outputQuad);

    //namedWindow("in", CV_WINDOW_AUTOSIZE);
    //namedWindow("out", CV_WINDOW_AUTOSIZE);

    while (1) {
        Mat in, gray, eq, out;
        Rect roi(0, 40, 639, 360);

        bool bSuccess = cap.read(in); // read a new frame from video
        if (!bSuccess) //if not success, break loop
        {
            cout << "Cannot read a frame from video stream" << endl;
            break;
        }

        cvtColor(in, gray, CV_BGR2GRAY);
//        equalizeHist(gray, eq);
        warpPerspective(gray, out, lambda, gray.size());
        Mat croppedImage = out(roi).clone();
        //Canny(frame, out, 50, 150, 3);

        //imshow("in", in);
        //imshow("out", croppedImage); //show the frame in "MyVideo" window

        imwrite("/tmp/birdview.jpg", croppedImage);
        upload();

        if (waitKey(5000) == 13) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            cout << "enter key is pressed by user" << endl;
            break;
        }
    }
    return 0;

}
