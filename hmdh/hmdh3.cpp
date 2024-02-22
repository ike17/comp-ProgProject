#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>
#include <cmath>
#include <stdexcept>

struct FileInfo {
    int blockSize;
    std::string experiment;
    int roi;
};

// Function to parse the filename and extract block size, experiment, and ROI
FileInfo parseFilename(const std::string& filename) {
    FileInfo info;
    // Assuming filename format is "expX_roiY_Z.txt" where X is experiment number, Y is ROI number, and Z is block size
    size_t pos1 = filename.find("exp") + 3;
    size_t pos2 = filename.find("_roi", pos1);
    size_t pos3 = filename.find("_", pos2 + 4);
    size_t pos4 = filename.find(".", pos3);

    info.experiment = filename.substr(pos1, pos2 - pos1);
    info.roi = std::stoi(filename.substr(pos2 + 4, pos3 - (pos2 + 4)));
    info.blockSize = std::stoi(filename.substr(pos3 + 1, pos4 - (pos3 + 1)));

    return info;
}

// Function to load time course data from a file
std::vector<double> loadTimeCourseData(const std::string& filename, FileInfo& fileInfo) {
    std::vector<double> data;
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    fileInfo = parseFilename(filename);

    double value;
    while (file >> value) {
        data.push_back(value);
    }

    file.close();
    return data;
}

// Function to generate the expected time course signal based on block size
std::vector<int> generateExpectedSignal(int blockSize, size_t dataSize) {
    std::vector<int> expectedSignal(dataSize);
    int currentSignal = 1; // Start with task period
    for (size_t i = 0; i < dataSize; ++i) {
        expectedSignal[i] = currentSignal;
        if ((i + 1) % blockSize == 0) {
            currentSignal = 1 - currentSignal; // Toggle between 0 and 1
        }
    }
    return expectedSignal;
}

// Function to compute Pearson correlation coefficient
double computePearsonCorrelation(const std::vector<double>& x, const std::vector<int>& y) {
    if (x.size() != y.size() || x.empty()) {
        throw std::invalid_argument("Vectors x and y must have the same size and cannot be empty.");
    }

    double sum_x = std::accumulate(x.begin(), x.end(), 0.0);
    double sum_y = std::accumulate(y.begin(), y.end(), 0);

    double sum_x2 = std::inner_product(x.begin(), x.end(), x.begin(), 0.0);
    double sum_y2 = std::inner_product(y.begin(), y.end(), y.begin(), 0);

    double sum_xy = std::inner_product(x.begin(), x.end(), y.begin(), 0.0);

    size_t n = x.size();
    double numerator = n * sum_xy - sum_x * sum_y;
    double denominator = std::sqrt((n * sum_x2 - sum_x * sum_x) * (n * sum_y2 - sum_y * sum_y));

    if (denominator == 0) {
        throw std::runtime_error("Division by zero in correlation calculation.");
    }

    return numerator / denominator;
}

int main() {
    std::string filename = "exp1_roi2_8.txt"; // Example file, replace with actual path if necessary

    FileInfo fileInfo;
    try {
        auto data = loadTimeCourseData(filename, fileInfo);
        auto expectedSignal = generateExpectedSignal(fileInfo.blockSize, data.size());

        double correlation = computePearsonCorrelation(data, expectedSignal);

        std::cout << "Correlation coefficient between actual data and expected signal for " << filename << ": "
                  << correlation << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;

    cout<< "naaks";

}
