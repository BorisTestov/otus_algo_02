#pragma once

#include <map>
#include "tester.h"
#include "math.h"

class TicketCounter : public ITask {
public:
    virtual std::string Run(std::vector<std::string> data) override final {
        std::string line = data.at(0);
        int n = std::atoi(line.c_str());
        /** Recursion
        unsigned long long luckyTicketsCounter = nextDigit(0, 0, 0, n);
         **/
        unsigned long long luckyTicketsCounter = getDigitSumms(n * 2, n * 9);
        return std::to_string(luckyTicketsCounter);
    }

private:
    /**
     * @brief Вычисляет количество n-значных чисел с суммой k
     * @param n - количество цифр в числе
     * @param k - искоммая сумма числа
     * @return количество n-значных чисел с суммой k
     */
    unsigned long long getDigitSumms(int n, int k) {
        if (n == 0) {
            return k == 0 ? 1 : 0;
        }
        unsigned long long summ = 0;
        for (int i = 0; i <= 9; ++i) {
            std::pair<int, int> key(n - 1, k - i);
            if (digitSumms.count(key) != 0) {
                summ += digitSumms.at(key);
            } else {
                unsigned long long result = getDigitSumms(n - 1, k - i);
                digitSumms[key] = result;
                summ += result;
            }
        }
        return summ;
    }

    unsigned long long nextDigit(int digit, int sum1, int sum2, int n, unsigned long long luckyTicketsCounter = 0) {
        if (digit == n) {
            if (sum1 == sum2) {
                luckyTicketsCounter++;
            }
            return luckyTicketsCounter;
        }
        for (int a = 0; a <= 9; ++a) {
            for (int b = 0; b <= 9; ++b) {
                luckyTicketsCounter = nextDigit(digit + 1, sum1 + a, sum2 + b, n, luckyTicketsCounter);
            }
        }
    }

    std::map<std::pair<int, int>, unsigned long long> digitSumms;
};