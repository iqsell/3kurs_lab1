#include "Bankomat.h"

Bankomat::Bankomat(string id, int minWithdrawAmount, int maxWithdrawAmount)
        : id(std::move(id)), minWithdrawAmount(minWithdrawAmount), maxWithdrawAmount(maxWithdrawAmount) {
    billCounts = { {1000, 5}, {500, 2}, {100, 0}, {50, 10}, {10, 5} };

    // Устанавливаем начальное значение currentAmount равным сумме номиналов купюр в банкомате
    currentAmount = 0;
    for (const auto& [bill, count] : billCounts) {
        currentAmount += bill * count;
    }
}

void Bankomat::loadMoney(int amount, map<int, int> bills) {
    if (amount > 0) {
        for (const auto& [bill, count] : bills) {
            if (billCounts.find(bill) != billCounts.end()) {
                billCounts[bill] += count;
            } else {
                // Не удалось найти номинал купюры в billCounts
                // Можно добавить обработку этой ситуации, если требуется
            }
        }
        updateCurrentAmount(); // Обновляем текущую сумму
    }
}

bool Bankomat::withdrawMoney(int amount, map<int, int>& withdrawnBills) {
    if (amount > getCurrentAmount()) {
        return false; // Недостаточно денег в банкомате для снятия указанной суммы
    }

    map<int, int> tempBillCounts = billCounts;

    for (auto it = billCounts.rbegin(); it != billCounts.rend(); ++it) {
        int bill = it->first;
        int count = min(amount / bill, billCounts[bill]); // Вычисляем количество купюр данного номинала, которое можно выдать
        if (count > 0) {
            withdrawnBills[bill] = count;
            amount -= bill * count; // Уменьшаем запрошенную сумму на сумму, которую удалось выдать купюрами данного номинала
            billCounts[bill] -= count; // Уменьшаем количество доступных купюр данного номинала
        }
    }

    if (amount > 0) {
        // Невозможно выдать запрошенную сумму
        // Возвращаем купюры обратно
        for (const auto& it : withdrawnBills) {
            int bill = it.first;
            int count = it.second;
            billCounts[bill] += count;
        }
        withdrawnBills.clear(); // Очищаем список снятых купюр
        return false;
    }

    updateCurrentAmount(); // Обновляем текущую сумму
    return true;
}

int Bankomat::getCurrentAmount() {
    return currentAmount;
}

void Bankomat::setCurrentAmount(int amount) {
    currentAmount = amount;
}

void Bankomat::updateCurrentAmount() {
    currentAmount = 0;
    for (const auto& [bill, count] : billCounts) {
        currentAmount += bill * count;
    }
}

string Bankomat::toString() const {
    string result = "Остаток в банкомате: " + std::to_string(currentAmount) + " рублей\n";
    result += "Купюр на 1000: " + std::to_string(billCounts.at(1000)) + "\n";
    result += "Купюр на 500: " + std::to_string(billCounts.at(500)) + "\n";
    result += "Купюр на 100: " + std::to_string(billCounts.at(100)) + "\n";
    result += "Купюр на 50: " + std::to_string(billCounts.at(50)) + "\n";
    result += "Купюр на 10: " + std::to_string(billCounts.at(10)) + "\n";
    return result;
}
// добавить проверки на ввод + добавить возможность внести изначальные значения в количество купюр в контекстном меню
