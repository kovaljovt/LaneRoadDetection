#include "RoadDetection.h"

cv::Mat RoadDetection::applyGrayscale(cv::Mat& source) {
    if (source.empty()) {
        std::cerr << "Input frame is empty" << '\n';
    }
    cv::Mat output;
    cv::cvtColor(source, output, cv::COLOR_BGR2GRAY);
    return output;
}

cv::Mat RoadDetection::applyGaussianBlur(cv::Mat& source) {
    if (source.empty()) {
        std::cerr << "Input frame is empty" << '\n';
    }
    cv::Mat output;
    cv::GaussianBlur(source, output, cv::Size(3, 3), 0);
    return output;
}

cv::Mat RoadDetection::applyCanny(cv::Mat &source) {
    if (source.empty()) {
        std::cerr << "The input image/frame is empty" << '\n';
    }
    cv::Mat output;
    cv::Canny(source, output, 50, 150);
    return output;
}

cv::Mat RoadDetection::filterColors(cv::Mat &source, bool isDayTime) {
    cv::Mat hsv;
    cv::Mat whiteImage;
    cv::Mat whiteMask;
    cv::Mat yellowImage;
    cv::Mat yellowMask;
    cv::Mat whiteYellow;

    if (source.empty()) {
        std::cerr << "The input image/frame is empty" << '\n';
    }

    /* white mask */
    std::vector<int> lowerWhite = {130, 130, 130};
    std::vector<int> upperWhite = {255, 255, 255};
    cv::inRange(source, lowerWhite, upperWhite, whiteMask);
    cv::bitwise_and(source, source, whiteImage, whiteMask);

    /* yellow mask */
    cv::cvtColor(source, hsv, cv::COLOR_BGR2HSV);
    std::vector<int> lowerYellow = {20, 100, 110};
    std::vector<int> upperYellow = {30, 180, 240};
    cv::inRange(hsv, lowerYellow, upperYellow, yellowMask);
    cv::bitwise_and(source, source, yellowImage, yellowMask);

    /* Blending yellow and white together */
    cv::addWeighted(whiteImage, 1., yellowImage, 1., 0., whiteYellow);

    /* Adding gray filter if image is not taken during the day */
    if (!isDayTime) {
        cv::Mat grayMask;
        cv::Mat grayImage;
        cv::Mat grayAndWhite;
        cv::Mat output;
        std::vector<int> lowerGray = {80, 80, 80};
        std::vector<int> upperGray = {130, 130, 130};
        cv::inRange(source, lowerGray, upperGray, grayMask);
        cv::addWeighted(grayImage, 1., whiteYellow, 1., 0., output);
        return output;
    }

    return whiteYellow;
}

bool RoadDetection::isDayTime(cv::Mat &source) {
    cv::Scalar sample = cv::mean(source);

    if (sample[0] < 30 || sample[1] < 33 && sample[2] < 30) {
        return false;
    }

    return true;
}

cv::Mat RoadDetection::regionOfInterest(cv::Mat &source) {
    /* big trapezoid */
    float trapezoidBottomWidth = 1.0;
    float trapezoidTopWidth = 0.07;
    float trapezoidHeight = 0.5;

    /* small trapezoid */
    float smallBottomWidth = 0.45;
    float smallTopWidth = 0.3;
    float smallHeight = 1.0;

    float bar = 0.97;

    std::vector<cv::Point> pts;

    /* big trapezoid */
    pts.emplace_back((source.cols * (1 - trapezoidBottomWidth)) / 2, source.rows * bar);
    pts.emplace_back((source.cols * (1 - trapezoidTopWidth)) / 2, source.rows - source.rows * trapezoidHeight);
    pts.emplace_back(source.cols - (source.cols * (1 - trapezoidTopWidth) ) / 2,
                     source.rows - source.rows * trapezoidHeight); // Top right
    pts.emplace_back(source.cols - (source.cols * (1 - trapezoidBottomWidth)) / 2,
                     source.rows * bar);

    /* small trapezoid */
    pts.emplace_back((source.cols * (1 - trapezoidBottomWidth + smallBottomWidth)) / 2,
                     source.rows * bar);
    pts.emplace_back((source.cols * (1 - trapezoidTopWidth * smallTopWidth)) / 2,
                     source.rows - source.rows * trapezoidHeight * smallHeight);
    pts.emplace_back(source.cols - (source.cols * (1 - trapezoidTopWidth * smallTopWidth)) / 2,
                     source.rows - source.rows * trapezoidHeight * smallHeight);
    pts.emplace_back(source.cols - (source.cols * (1 - trapezoidBottomWidth + smallBottomWidth)) / 2,
                     source.rows * bar);

    cv::Mat mask = cv::Mat::zeros(source.size(), source.type());
    cv::fillPoly(mask, pts, cv::Scalar(255, 255, 255));

    cv::Mat maskedImage;
    cv::bitwise_and(source, mask, maskedImage);

    return maskedImage;
}

std::vector<cv::Vec4i> RoadDetection::houghLines(cv::Mat &canny,
                                                 cv::Mat &source,
                                                 bool drawHough) {
    double rho = 2;
    double theta = 1 * M_PI / 180;
    int thresh = 15;
    double minLineLength = 10;
    double maxGapLength = 20;

    std::vector<cv::Vec4i> linesP;
    cv::HoughLinesP(canny, linesP, rho, theta, thresh, minLineLength, maxGapLength);

    if (drawHough) {
        for (size_t i = 0; i < linesP.size(); i++) {
            cv::Vec4i l = linesP[i];
            cv::line(source, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]),
                   cv::Scalar(0,0,255), 3, cv::LINE_AA);
        }
        cv::imshow("Hough Lines", source);
        cv::waitKey();
    }

    return linesP;
}

cv::Mat RoadDetection::drawLanes(cv::Mat &source, std::vector<cv::Vec4i> lines) {
    if (lines.size() == 0) {
        return source;
    }

    // Set drawing lanes to true
    bool drawRightLane = true;
    bool drawLeftLane = true;

    // Find lines with a slope higher than the slope threshold
    float slopeThreshold = 0.5;
    std::vector<float> slopes;
    std::vector<cv::Vec4i> goodLines;

    for (int i = 0; i < lines.size(); i++) {
        cv::Vec4i l = lines[i];
        double slope;

        if (l[2] - l[0] == 0) {
            slope = 999;
        } else {
            slope = (l[3] - l[1]) / (l[2] / l[0]);
        }
        if (abs(slope) > 0.5) {
            slopes.push_back(slope);
            goodLines.push_back(l);
        }
    }

    std::vector<cv::Vec4i> rightLines;
    std::vector<cv::Vec4i> leftLines;
    int imgCenter = source.cols / 2;

    for (int i = 0; i < slopes.size(); i++)
    {
        if (slopes[i] > 0 && goodLines[i][0] > imgCenter && goodLines[i][2] > imgCenter)
        {
            rightLines.push_back(goodLines[i]);
        }
        if (slopes[i] < 0 && goodLines[i][0] < imgCenter && goodLines[i][2] < imgCenter)
        {
            leftLines.push_back(goodLines[i]);
        }
    }

    // We start with the right side points
    std::vector< int > rightLinesX;
    std::vector< int > rightLinesY;
    double rightB1, rightB0; // Slope and intercept

    for (int i = 0; i < rightLines.size(); i++)
    {
        rightLinesX.push_back(rightLines[i][0]); // X of starting point of line
        rightLinesX.push_back(rightLines[i][2]); // X of ending point of line
        rightLinesY.push_back(rightLines[i][1]); // Y of starting point of line
        rightLinesY.push_back(rightLines[i][3]); // Y of ending point of line
    }

    if (rightLinesX.size() > 0)
    {
        std::vector< double > coefficientRight = estimateCoefficients<int, double>(rightLinesX, rightLinesY); // y = b1x + b0
        rightB1 = coefficientRight[0];
        rightB0 = coefficientRight[1];
    } else {
        rightB1 = 1;
        rightB0 = 1;
        drawRightLane = false;
    }

    std::vector< int > leftLinesX;
    std::vector< int > leftLinesY;
    double leftB1, leftB0; // Slope and intercept

    for (int i = 0; i < leftLines.size(); i++)
    {
        leftLinesX.push_back(leftLines[i][0]); // X of starting point of line
        leftLinesX.push_back(leftLines[i][2]); // X of ending point of line
        leftLinesY.push_back(leftLines[i][1]); // Y of starting point of line
        leftLinesY.push_back(leftLines[i][3]); // Y of ending point of line
    }

    if (leftLinesX.size() > 0) {
        std::vector< double > coefficientLeft = estimateCoefficients<int, double>(leftLinesX, leftLinesY); // y = b1x + b0
        leftB1 = coefficientLeft[0];
        leftB0 = coefficientLeft[1];
    } else {
        leftB1 = 1;
        leftB0 = 1;
        drawLeftLane = false;
    }
}
