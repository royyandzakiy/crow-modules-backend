// database/DatabaseConnection.cpp
module;

#include <SQLiteCpp/SQLiteCpp.h>

import std;

export module database;

export class DatabaseConnection {
  private:
	std::unique_ptr<SQLite::Database> db_;
	std::mutex mutex_;

  public:
	explicit DatabaseConnection(const std::string &db_path);

	// No Copy
	DatabaseConnection(const DatabaseConnection &) = delete;
	DatabaseConnection &operator=(const DatabaseConnection &) = delete;

	// Thread-safe to execute
	template <typename Func> auto execute(Func &&func) -> decltype(func(*db_)) {
		std::lock_guard lock(mutex_);
		return func(*db_);
	}

	void beginTransaction();
	void commit();
	void rollback();

	void initializeSchema();
};

// rewrite the below pls
/*
export class DatabaseConnection {
  private:
	std::unique_ptr<SQLite::Database> db_;
	std::mutex mutex_;

  public:
	explicit DatabaseConnection(const std::string &db_path);

	// RAII: No copying
	DatabaseConnection(const DatabaseConnection &) = delete;
	DatabaseConnection &operator=(const DatabaseConnection &) = delete;

	// Thread-safe execute
	template <typename Func> auto execute(Func &&func) -> decltype(func(*db_)) {
		std::lock_guard lock(mutex_);
		return func(*db_);
	}

	// For transactions
	void beginTransaction();
	void commit();
	void rollback();

	// Initialize schema
	void initializeSchema();
};

DatabaseConnection::DatabaseConnection(const std::string &db_path) {
	try {
		db_ = std::make_unique<SQLite::Database>(db_path, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
		std::cout << "Connected to database: " << db_path << std::endl;
		initializeSchema();
	} catch (const SQLite::Exception &e) {
		std::cerr << "Database connection failed: " << e.what() << std::endl;
		throw;
	}
}

void DatabaseConnection::initializeSchema() {
	execute([this](SQLite::Database &db) {
		// Create users table
		db.exec(R"(
			CREATE TABLE IF NOT EXISTS users (
				id INTEGER PRIMARY KEY AUTOINCREMENT,
				name TEXT NOT NULL,
				created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
			)
		)");

		// Create posts table
		db.exec(R"(
			CREATE TABLE IF NOT EXISTS posts (
				id INTEGER PRIMARY KEY AUTOINCREMENT,
				title TEXT NOT NULL,
				content TEXT NOT NULL,
				author_id INTEGER NOT NULL,
				created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
				FOREIGN KEY (author_id) REFERENCES users(id) ON DELETE CASCADE
			)
		)");

		// Create indexes
		db.exec("CREATE INDEX IF NOT EXISTS idx_posts_author_id ON posts(author_id)");

		return 0; // Return type must match Func return
	});
}

void DatabaseConnection::beginTransaction() {
	execute([](SQLite::Database &db) {
		db.exec("BEGIN TRANSACTION");
		return 0;
	});
}

void DatabaseConnection::commit() {
	execute([](SQLite::Database &db) {
		db.exec("COMMIT");
		return 0;
	});
}

void DatabaseConnection::rollback() {
	execute([](SQLite::Database &db) {
		db.exec("ROLLBACK");
		return 0;
	});
}
*/