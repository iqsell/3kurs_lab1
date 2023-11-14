#include <iostream>
#include <limits>
#include "Bankomat.h"

using namespace std;

int main() {
    Bankomat atm("ATM001", 100, 5000);
    int option;

    while (true) {
        // Выводим контекстное меню
        cout << "-----------------" << endl;
        cout << "1. Загрузить деньги в банкомат" << endl;
        cout << "2. Снять деньги из банкомата" << endl;
        cout << "3. Вывести остаток денег в банкомате" << endl;
        cout << "0. Выйти из меню" << endl;
        cout << "Выберите опцию: ";

        cin >> option;

        // Проверка на корректный ввод опции
        while (cin.fail() || (option < 0 || option > 3)) {
            cin.clear(); // Сброс флага ошибки ввода
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода
            cout << "Неверная опция. Пожалуйста, выберите допустимую опцию: ";
            cin >> option;
        }

        switch (option) {
            case 1: {
                map<int, int> billsToAdd;
                int nominal, count;
                do {
                    cout << "Введите номинал купюры (или 0 для завершения): ";
                    cin >> nominal;

                    // Проверка на корректный ввод номинала
                    while (cin.fail() || nominal < 0) {
                        cin.clear(); // Сброс флага ошибки ввода
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода
                        cout << "Неверный номинал. Пожалуйста, введите корректный номинал купюры: ";
                        cin >> nominal;
                    }

                    if (nominal == 0) {
                        break;
                    }
                    cout << "Введите количество купюр данного номинала: ";
                    cin >> count;

                    // Проверка на корректный ввод количества купюр
                    while (cin.fail() || count < 0) {
                        cin.clear(); // Сброс флага ошибки ввода
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода
                        cout << "Неверное количество купюр. Пожалуйста, введите корректное количество: ";
                        cin >> count;
                    }

                    billsToAdd[nominal] = count;
                } while (true);

                int totalAmount = 0;
                for (const auto &[bill, count]: billsToAdd) {
                    totalAmount += bill * count;
                }
                atm.loadMoney(totalAmount, billsToAdd);
                break;
            }
            case 2: {
                int amountToWithdraw;
                cout << "Введите сумму для снятия: ";

                cin >> amountToWithdraw;

                // Проверка на корректный ввод суммы для снятия
                while (cin.fail() || amountToWithdraw < 0) {
                    cin.clear(); // Сброс флага ошибки ввода
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера ввода
                    cout << "Неверная сумма. Пожалуйста, введите корректную сумму для снятия: ";
                    cin >> amountToWithdraw;
                }

                map<int, int> withdrawnBills;
                bool success = atm.withdrawMoney(amountToWithdraw, withdrawnBills);
                if (success) {
                    cout << "Сняты купюры следующего номинала:" << endl;
                    for (const auto& [bill, count] : withdrawnBills) {
                        cout << "Номинал: " << bill << ", количество: " << count << endl;
                    }
                } else {
                    cout << "Недостаточно средств в банкомате" << endl;
                }
                break;
            }

            case 3: {
                cout << atm.toString() << endl;
                break;
            }

            case 0: {
                cout << "До свидания!" << endl;
                return 0;
            }
        }
    }
    return 0;
}
// реализоваить fraction функционал, LongLong свойства, сеттер геттер и все смысл в том, чтобы не вводить свойства в fraction а взять их из Longlong