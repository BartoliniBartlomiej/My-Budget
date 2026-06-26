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
};