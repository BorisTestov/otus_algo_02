#pragma once

#include <string>
#include <memory>
#include <fstream>
#include <vector>
#include <iostream>
#include <chrono>
#include <algorithm>

inline bool fileExists(const std::string &name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

class ITask {
public:
    virtual std::string Run(std::vector<std::string>) = 0;
};

using ITaskPtr = std::shared_ptr<ITask>;

class Tester {
public:
    Tester() = delete;

    Tester(ITaskPtr task, const std::string &path) {
        this->task = task;
        this->path = path;
    }

    void RunTests(bool verbose = false) {
        int testNumber = 0;
        std::cout << "Tester started: " << std::endl;
        while (true) {
            std::cout << "_______________________________" << std::endl;
            std::string inFile = path + "/test." + std::to_string(testNumber) + ".in";
            std::string outFile = path + "/test." + std::to_string(testNumber) + ".out";
            if (!fileExists(inFile) || !fileExists(outFile))
                break;
            auto start = std::chrono::high_resolution_clock::now();
            bool result = RunTest(inFile, outFile, verbose);
            auto stop = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
            std::string testResult = "Passed";
            if (!result) {
                testResult = "Failed";
            }
            std::cout << "Test#" << testNumber << "\t" << testResult << "\t" << elapsed << "ms"
                      << std::endl;
            testNumber++;
        }
    }

private:
    bool RunTest(std::string infile, std::string outfile, bool verbose) {
        try {
            // Read array of str from input file
            std::vector<std::string> data;
            std::ifstream inputFile(infile);
            std::string line;
            while (std::getline(inputFile, line)) {
                line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
                line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
                data.push_back(line);
            }
            // Read one line from output file
            std::ifstream outputFile(outfile);
            std::string expect;
            std::getline(outputFile, expect);
            expect.erase(std::remove(expect.begin(), expect.end(), '\n'), expect.end());
            expect.erase(std::remove(expect.begin(), expect.end(), '\r'), expect.end());
            std::string actual = task->Run(data);
            if (verbose) {
                std::cout << "Expected: " << expect << std::endl;
                std::cout << "Actual: " << actual << std::endl;
            }
            return expect == actual;
        }
        catch (std::exception e) {
            std::cout << e.what() << std::endl;
            return false;
        }
    }

    ITaskPtr task;
    std::string path;
};