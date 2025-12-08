// database/DatabaseConnection.cpp
module;

#include <SQLiteCpp/SQLiteCpp.h>

import <memory>;
import <mutex>;

export module database;

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