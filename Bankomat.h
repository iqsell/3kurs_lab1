#ifndef BANKOMAT_H
#define BANKOMAT_H

#include <string>
#include <map>

using namespace std;

class Bankomat {
public:
    Bankomat(string id, int minWithdrawAmount, int maxWithdrawAmount); // убираем currentAmount из параметров

    void loadMoney(int amount, map<int, int> bills);
    bool withdrawMoney(int amount, map<int, int>& withdrawnBills);
    int getCurrentAmount();
    void setCurrentAmount(int amount);
    string toString() const;

private:
    string id;
    int currentAmount;
    int minWithdrawAmount;
    int maxWithdrawAmount;
    map<int, int> billCounts;

    void updateCurrentAmount(); // Добавляем объявление для updateCurrentAmount
};

#endif // BANKOMAT_H
