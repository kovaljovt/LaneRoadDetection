#pragma once

#include <vector>
#include <numeric>

#include <opencv2/opencv.hpp>


template<typename T, typename X>
X multiplyAndSum(std::vector<T> A, std::vector<T> B) {
    X sum;
    std::vector<T> temp;
    for (int i = 0; i < A.size(); i++) {
        temp.push_back(A[i] * B[i]);
    }
    sum = std::accumulate(temp.begin(), temp.end(), 0.0);
    return sum;
}


template<typename T, typename X>
std::vector<X> estimateCoefficients(std::vector<T> A, std::vector<T> B) {
    int N = A.size();
    X meanA = std::accumulate(A.begin(), A.end(), 0.0) / A.size();
    X meanB = std::accumulate(B.begin(), B.end(), 0.0) / B.size();

    X SSxy = multiplyAndSum<T, T>(A, B) - (N * meanA * meanB);
    X SSxx = multiplyAndSum<T, T>(A, A) - (N * meanA * meanA);

    X slopeB1 = SSxy / SSxx;
    X interceptB0 = meanB - (slopeB1 * meanA);

    std::vector<X> coefficient;
    coefficient.push_back(slopeB1);
    coefficient.push_back(interceptB0);

    return coefficient;
}