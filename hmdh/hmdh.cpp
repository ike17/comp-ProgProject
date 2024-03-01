#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <regex>

using namespace std

// Struct to hold metadata extracted from filename
struct FileInfo {
    int experimentNumber;
    int roiNumber;
    int blockSize;
};

// Function to extract experiment number, ROI, and block size from filename
FileInfo parseFilename(const std::string& filename) {
    std::regex pattern("exp(\\d+)_roi(\\d+)_(\\d+).txt");
    std::smatch matches;
    if (std::regex_search(filename, matches, pattern) && matches.size() == 4) {
        return FileInfo{
            std::stoi(matches[1].str()), // Experiment number
            std::stoi(matches[2].str()), // ROI number
            std::stoi(matches[3].str())  // Block size
        };
    } else {
        throw std::runtime_error("Failed to parse filename: " + filename);
    }
}

// Function to read time course data from file
std::vector<double> loadTimeCourseData(const std::string& filename, FileInfo& fileInfo) {
    fileInfo = parseFilename(filename); // Extract metadata from filename

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::vector<double> data;
    double value;
    while (file >> value) {
        data.push_back(value);
    }
    return data;
}

// Function to generate expected time course signal
std::vector<int> generateExpectedSignal(int blockSize, int dataSize) {
    std::vector<int> expectedSignal(dataSize);
    bool currentSignal = 1; // Start with task period (1)
    for (int i = 0; i < dataSize; ++i) {
        expectedSignal[i] = currentSignal;
        if ((i + 1) % blockSize == 0) {
            currentSignal = !currentSignal; // Toggle between rest and task
        }
    }
    return expectedSignal;
}

int main() {
    std::vector<std::string> filenames = {
        "exp1_roi2_8.txt",
        "exp1_roi1_8.txt",
        "exp2_roi2_16.txt",
        "exp2_roi1_16.txt"
    };

    for (const auto& filename : filenames) {
        FileInfo fileInfo;
        try {
            auto data = loadTimeCourseData(filename, fileInfo);
            std::cout << "Filename: " << filename 
                      << "\nExperiment Number: " << fileInfo.experimentNumber
                      << ", ROI Number: " << fileInfo.roiNumber
                      << ", Block Size: " << fileInfo.blockSize
                      << "\nData Size: " << data.size() << std::endl << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;

    // Inside your main function, after loading the data
    FileInfo fileInfo;
    auto data = loadTimeCourseData(filenames, fileInfo);
    std::cout << "Filename: " << filenames 
          << "\nExperiment Number: " << fileInfo.experimentNumber
          << ", ROI Number: " << fileInfo.roiNumber
          << ", Block Size: " << fileInfo.blockSize
          << "\nData Size: " << data.size() << std::endl;

    // Generate expected signal
    auto expectedSignal = generateExpectedSignal(fileInfo.blockSize, data.size());

    // Now, you have both the actual time course data and the expected signal for further analysis.

}
