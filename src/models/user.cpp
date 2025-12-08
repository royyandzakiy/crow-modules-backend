module;

import std;

export module user;

export class User {
  public:
	int id_;
	std::string name_;

	User() = default;
	User(const int id, const std::string &name) : id_(id), name_(name) {
	}
};