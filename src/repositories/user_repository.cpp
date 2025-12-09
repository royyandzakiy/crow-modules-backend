// repositories/UserRepository.cpp
module;

#include <SQLiteCpp/SQLiteCpp.h>

import std;

import user;
import database;
export module user_repository;

// rewrite pls
// export class UserRepository {
//   private:
// 	DatabaseConnection &db_;

//   public:
// 	explicit UserRepository(DatabaseConnection &db) : db_(db) {
// 	}

// 	// CRUD operations
// 	std::optional<User> findById(int id);
// 	std::vector<User> findAll();
// 	int create(const User &user);
// 	bool update(const User &user);
// 	bool deleteById(int id);
// 	int count();

//   private:
// 	User userFromRow(const SQLite::Statement &stmt);
// };

// std::optional<User> UserRepository::findById(int id) {
// 	return db_.execute([id](SQLite::Database &db) -> std::optional<User> {
// 		SQLite::Statement query(db, "SELECT id, name FROM users WHERE id = ?");
// 		query.bind(1, id);

// 		if (query.executeStep()) {
// 			return User{query.getColumn(0).getInt(), query.getColumn(1).getString()};
// 		}
// 		return std::nullopt;
// 	});
// }

// std::vector<User> UserRepository::findAll() {
// 	return db_.execute([](SQLite::Database &db) -> std::vector<User> {
// 		std::vector<User> users;
// 		SQLite::Statement query(db, "SELECT id, name FROM users ORDER BY id");

// 		while (query.executeStep()) {
// 			users.emplace_back(query.getColumn(0).getInt(), query.getColumn(1).getString());
// 		}
// 		return users;
// 	});
// }

// int UserRepository::create(const User &user) {
// 	return db_.execute([&user](SQLite::Database &db) -> int {
// 		SQLite::Statement query(db, "INSERT INTO users (name) VALUES (?) RETURNING id");
// 		query.bind(1, user.name_);

// 		if (query.executeStep()) {
// 			return query.getColumn(0).getInt();
// 		}
// 		throw std::runtime_error("Failed to create user");
// 	});
// }

// bool UserRepository::update(const User &user) {
// 	return db_.execute([&user](SQLite::Database &db) -> bool {
// 		SQLite::Statement query(db, "UPDATE users SET name = ? WHERE id = ?");
// 		query.bind(1, user.name_);
// 		query.bind(2, user.id_);

// 		return query.exec() > 0;
// 	});
// }

// bool UserRepository::deleteById(int id) {
// 	return db_.execute([id](SQLite::Database &db) -> bool {
// 		SQLite::Statement query(db, "DELETE FROM users WHERE id = ?");
// 		query.bind(1, id);

// 		return query.exec() > 0;
// 	});
// }

// int UserRepository::count() {
// 	return db_.execute([](SQLite::Database &db) -> int {
// 		SQLite::Statement query(db, "SELECT COUNT(*) FROM users");
// 		query.executeStep();
// 		return query.getColumn(0).getInt();
// 	});
// }