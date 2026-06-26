#pragma once 

#include <string>
#include <vector>
#include <iostream>

#include "Transaction.hpp"

class User {
    int id;
    std::string name;
    std::string surname;
    std::string login;
    std::string password;

    std::vector<Transaction> transactions;
    
public:
    User(const std::string& login, const std::string& plainPassword)
        : login(login),
          password(plainPassword)
    {}
    User() {}

    int getId() const                   {   return id;          }
    std::string getName() const         {   return name;        }
    std::string getSurname() const      {   return surname;     }
    std::string getLogin() const        {   return login;       }
    std::string getPassword() const     {   return password;    }

    void setId(int id)                  {   this->id = id;      }
    void setName(const std::string& name)         {   this->name = name;  }
    void setSurname(const std::string& surname)   {   this->surname = surname; }
    void setLogin(const std::string& login)       {   this->login = login; }
    void setPassword(const std::string& password) {   this->password = password; }

    void addTransaction(const Transaction& newTransaction) {
        transactions.push_back(newTransaction);
    }

    const std::vector<Transaction>& getTransactions() const {
        return transactions;
    }

    const void printTransactions() const {
        for (const auto& transaction : transactions) {
            std::cout << "Transaction ID: " << transaction.getId() << std::endl;
            std::cout << "User ID: " << transaction.getUserId() << std::endl;
            std::cout << "Category ID: " << transaction.getCategoryId() << std::endl;
            std::cout << "Type: " << static_cast<int>(transaction.getCategoryType()) << std::endl;
            std::cout << "Amount: " << transaction.getAmount() << std::endl;
            std::cout << "Title: " << transaction.getTitle() << std::endl;
            std::cout << "Description: " << transaction.getDescription() << std::endl;
            std::cout << "Date: " << transaction.getDate() << std::endl;

            if(transaction.isRecurring()) {
                std::cout << "Recurrence: " << static_cast<int>(transaction.getRecurrence()) << std::endl;
                std::cout << "Recurrence End Date: " << transaction.getRecurrenceEndDate() << std::endl;
                std::cout << "------------------------" << std::endl;
            }
        }
    }

};