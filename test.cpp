#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
    VideoCapture video(0);  // Use camera index 0 (default webcam)

    if (!video.isOpened()) {
        cerr << "Error: Could not open the camera." << endl;
        return 1;
    }

    CascadeClassifier facedetect;
    if (!facedetect.load("D:/software/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml")) {
        cerr << "Error: Could not load face cascade." << endl;
        return 1;
    }

    Mat img;
    while (true) {
        video.read(img);
        if (img.empty()) {
            cerr << "Error: Could not read from the camera." << endl;
            break;
        }

        vector<Rect> faces;
        facedetect.detectMultiScale(img, faces, 1.3, 5);

        for (const Rect& face : faces) {
            rectangle(img, face.tl(), face.br(), Scalar(50, 50, 255), 3);
        }

        imshow("Frame", img);

        if (waitKey(1) == 27)  // Exit the loop when Esc key is pressed
            break;
    }

    return 0;
}
