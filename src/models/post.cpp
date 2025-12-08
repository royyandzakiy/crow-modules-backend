module;

import std;

export module post;

export class Post {
  public:
	int id_;
	std::string title_;
	std::string content_;
	int author_id_;

	Post() = default;
	Post(const int id, const std::string &title, const std::string &content, const int author_id)
		: id_(id), title_(title), content_(content), author_id_(author_id) {
	}
};