#pragma once

#include <QSqlDatabase>
#include <QString>

class DatabaseManager {
private:
    QSqlDatabase db;
    static DatabaseManager* instance;
    
    DatabaseManager();

    bool createTables();

public:
    static DatabaseManager& getInstance();

    bool init(const QString& dbName = "budget.db");
    
    QSqlDatabase getDatabase() const;
    ~DatabaseManager();

    void     saveLastUser(int userId);
    int      loadLastUserId();
    void     clearLastUser();
};