#include <opencv2/opencv.hpp>
#include <iostream>
//#include <cmath>

using namespace std;
using namespace cv;

int main() {

    string filenames[] = { "../../image/Gear1.jpg", "../../image/Gear2.jpg", "../../image/Gear3.jpg", "../../image/Gear4.jpg" };

    for (int i = 0; i < 4; ++i) {
        Mat src = imread(filenames[i]);
        imshow("#1 Image " + to_string(i + 1), src);

        Mat gray, edge;
        cvtColor(src, gray, COLOR_BGR2GRAY);
        threshold(gray, edge, 150, 255, THRESH_BINARY);

        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        findContours(edge, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        Mat dst = src.clone();
        drawContours(dst, contours, -1, Scalar(0, 255, 0), 2);

        Point2f center_gear;
        for (size_t j = 0; j < contours.size(); ++j) {
            float radius;
            minEnclosingCircle(contours[j], center_gear, radius);
            circle(dst, center_gear, (int)radius, Scalar(255, 0, 0), 2);
        }

        Point2f closestPoint;
        double minDistance = DBL_MAX;
        for (int j = 0; j < contours[0].size(); j++) {
            Point2f point = contours[0][j];
            double distance = norm(center_gear - point);

            if (distance < minDistance) {
                minDistance = distance;
                closestPoint = point;
            }
        }
        double radius = norm(center_gear - closestPoint);
        //cout << "Radius: " << radius << endl;


        circle(dst, center_gear, (int)radius + 4, Scalar(255, 0, 0), 2);
        Mat gear_tooth = src.clone();
        circle(gear_tooth, center_gear, (int)radius + 4, Scalar(0, 0, 0), -1);

        cvtColor(gear_tooth, gray, COLOR_BGR2GRAY);
        threshold(gray, edge, 128, 255, THRESH_BINARY);
        findContours(edge, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        Mat finalDst_val = gear_tooth.clone();

        double total = 0;
        for (int j = 0; j < contours.size(); ++j) {
            Moments m = moments(contours[j]);
            total += m.m00;
        }
        double avg_pixel = total / contours.size();

        float ratio = 0.25;
        Mat contour_Img = finalDst_val.clone();
        for (int j = 0; j < contours.size(); ++j) {
            Moments m = moments(contours[j]);
            Point2f center(m.m10 / m.m00 - 20, m.m01 / m.m00);
            Scalar Color = (m.m00 < avg_pixel - 200 || m.m00 > avg_pixel + 200) ? Scalar(0, 0, 255) : Scalar(0, 255, 0);
            drawContours(contour_Img, contours, j, Color, 2);
        }

        // **putText 적용 전의 이미지 출력 (두 번째로)** 
        for (int j = 0; j < contours.size(); ++j) {
            Moments m = moments(contours[j]);
            Point2f center(m.m10 / m.m00 - 20, m.m01 / m.m00);

            // 컨투어 색상 결정
            Scalar Color = (m.m00 < avg_pixel - 200 || m.m00 > avg_pixel + 200) ? Scalar(0, 0, 255) : Scalar(0, 255, 0);
            drawContours(finalDst_val, contours, j, Color, 2);

            Point2f textPosition = center * (1 - ratio) + center_gear * ratio;
            Scalar textColor = Color; 

            // Draw the pixel count under the contour
            putText(finalDst_val, to_string((int)m.m00), textPosition, FONT_HERSHEY_SIMPLEX, 0.4, textColor, 1);
        }

        imshow("#2 Final Image with Text " + to_string(i + 1), finalDst_val);
        imshow("#3 Contour Only Image " + to_string(i + 1), contour_Img);

        Mat check_Img = src.clone();
        int badTeeth = 0; 
        for (int j = 0; j < contours.size(); ++j) {
            Moments m = moments(contours[j]);
            Point2f center(m.m10 / m.m00, m.m01 / m.m00);

            if (m.m00 < avg_pixel - 200 || m.m00 > avg_pixel + 200) {
                badTeeth++;
            }
        }

        cout << "기어 " << i + 1 << "의 불량 이빨 수: " << badTeeth << ", 이뿌리 원의 지름: " << radius*2 << "Avg_teeth_area: "<<avg_pixel<< endl;

        imshow("#4 check bad teeth " + to_string(i + 1), check_Img);
    }

    waitKey(0);

    return 0;
}
