#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Please input numbers to find average." << std::endl;
        return 1;
    }

    std::vector<double> numbers;
    int sum = 0.0;

    for (int i = 1; i < argc; ++i) {
        int num = std::atof(argv[i]);
        numbers.push_back(num);
        sum += num;
    }

    int average = sum / numbers.size();
    
    std::cout << "---------------------------------" << std::endl;
    std::cout << "Average of " << numbers.size() << " numbers = " 
              << std::fixed << std::setprecision(3) << average << std::endl;
    std::cout << "---------------------------------" << std::endl;
    
    return 0;
}

