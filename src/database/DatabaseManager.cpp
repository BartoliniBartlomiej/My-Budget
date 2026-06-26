#include "../../include/database/DatabaseManager.hpp"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DatabaseManager* DatabaseManager::instance = nullptr;

DatabaseManager& DatabaseManager::getInstance() {
    if (!instance) {
        instance = new DatabaseManager();
    }
    return *instance;
}

DatabaseManager::DatabaseManager() {}

DatabaseManager::~DatabaseManager() {
    if (db.isOpen()) {
        db.close();
    }
}

bool DatabaseManager::init(const QString& dbName) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    if (!db.open()) {
        qDebug() << "Blad otwarcia bazy danych:" << db.lastError().text();
        return false;
    }

    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON;");

    return createTables();
}

bool DatabaseManager::createTables() {
    QSqlQuery query;

    // User table
    bool uOk = query.exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT UNIQUE NOT NULL, "
        "password_hash TEXT NOT NULL"
        ");"
    );

    // Category table
    bool cOk = query.exec(
        "CREATE TABLE IF NOT EXISTS categories ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "type TEXT NOT NULL, "
        "user_id INTEGER NOT NULL"
        ");"
    );

    // Transaction table
    bool tOk = query.exec(
        "CREATE TABLE IF NOT EXISTS transactions ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "amount REAL NOT NULL, "
        "category_id INTEGER NOT NULL, "
        "date TEXT NOT NULL, "
        "description TEXT, "
        "user_id INTEGER NOT NULL, "
        "FOREIGN KEY(user_id) REFERENCES users(id) ON DELETE CASCADE, "
        "FOREIGN KEY(category_id) REFERENCES categories(id)"
        ");"
    );

    if (!uOk || !cOk || !tOk) {
        qDebug() << "Blad podczas tworzenia tabel:" << query.lastError().text();
        return false;
    }

    return true;
}

QSqlDatabase DatabaseManager::getDatabase() const {
    return db;
}