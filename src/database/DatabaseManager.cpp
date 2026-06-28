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
        qDebug() << "Initialisation error:" << db.lastError().text();
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
        "title TEXT NOT NULL DEFAULT '', "
        "description TEXT, "
        "type TEXT NOT NULL DEFAULT 'EXPENSE', "
        "user_id INTEGER NOT NULL, "
        "FOREIGN KEY(user_id) REFERENCES users(id) ON DELETE CASCADE, "
        "FOREIGN KEY(category_id) REFERENCES categories(id)"
        ");"
    );

    bool sOk = query.exec(
        "CREATE TABLE IF NOT EXISTS app_settings ("
        "key TEXT PRIMARY KEY, "
        "value TEXT NOT NULL"
        ");"
    );

    if (!uOk || !cOk || !tOk || !sOk) {
        qDebug() << "Error while creating tables:" << query.lastError().text();
        return false;
    }

    return true;
}

QSqlDatabase DatabaseManager::getDatabase() const {
    return db;
}

void DatabaseManager::saveLastUser(int userId) {
    QSqlQuery q;
    q.prepare("INSERT OR REPLACE INTO app_settings (key, value) VALUES ('last_user_id', :val)");
    q.bindValue(":val", userId);
    q.exec();
}

int DatabaseManager::loadLastUserId() {
    QSqlQuery q;
    q.prepare("SELECT value FROM app_settings WHERE key = 'last_user_id'");
    if (q.exec() && q.next()) {
        bool ok;
        int id = q.value(0).toInt(&ok);
        return ok ? id : -1;
    }
    return -1;
}

void DatabaseManager::clearLastUser() {
    QSqlQuery q;
    q.exec("DELETE FROM app_settings WHERE key = 'last_user_id'");
}