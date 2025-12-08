#include <crow.h>

import <unordered_map>;
import std;

class User {
  public:
	int id_;
	std::string name_;

	User() = default;
	User(const int id, const std::string &name) : id_(id), name_(name) {
	}
};

class Post {
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

std::unordered_map<int, User> g_users;
std::unordered_map<int, Post> g_posts;
int g_user_id_count = 0;
int g_post_id_count = 0;

int main() {
	g_users.reserve(100);
	g_users.reserve(1000);

	std::println("Crow Start!");

	crow::SimpleApp app; // define your crow application

	// PRE-LOAD INITIAL DATA EFFICIENTLY
	g_users.try_emplace(1, 1, "Alice Smith");
	g_users.try_emplace(2, 2, "Bob Johnson");
	g_users.try_emplace(3, 3, "Charlie Brown");
	g_user_id_count = 3;

	g_posts.try_emplace(101, 101, "Modern C++", "C++20/23 Features", 1);
	g_posts.try_emplace(102, 102, "Concurrency", "Threads and async", 2);
	g_posts.try_emplace(103, 103, "Modules", "C++20 Modules", 1);
	g_post_id_count = 103;

	CROW_ROUTE(app, "/")([]() {								 //
		auto page = crow::mustache::load_text("index.html"); //
		return page;										 //
	});

	// USERS
	CROW_ROUTE(app, "/users").methods("POST"_method)([](const crow::request &req) {
		auto json = crow::json::load(req.body);
		if (!json || !json.has("name")) {
			return crow::response(400, "Missing 'name' field");
		}

		int id = ++g_post_id_count;
		g_users[id] = User(id, json["name"].s());

		crow::json::wvalue response;
		response["id"] = id;
		response["name"] = json["name"].s();
		return crow::response(response);
	});

	CROW_ROUTE(app, "/users").methods("GET"_method)([]() {
		crow::json::wvalue usersArray;
		int i = 0;
		for (const auto &[id, name] : g_users) {
			crow::json::wvalue userJson;
			userJson["id"] = id;
			userJson["name"] = &name;
			usersArray[++i] = std::move(userJson);
		}
		return crow::response(usersArray);
	});

	CROW_ROUTE(app, "/users/<int>").methods("GET"_method)([](int userId) {
		auto it = g_users.find(userId);
		if (it == g_users.end()) {
			return crow::response(404, "User not found");
		}

		crow::json::wvalue response;
		response["id"] = it->second.id_;
		response["name"] = it->second.name_;
		return crow::response(response);
	});

	CROW_ROUTE(app, "/users/<int>").methods("PUT"_method)([](const crow::request &req, int userId) {
		auto it = g_users.find(userId);
		if (it == g_users.end()) {
			return crow::response(404, "User not found");
		}

		auto json = crow::json::load(req.body);
		if (!json || !json.has("name")) {
			return crow::response(400, "Missing 'name' field");
		}

		it->second.name_ = json["name"].s();

		crow::json::wvalue response;
		response["id"] = it->second.id_;
		response["name"] = it->second.name_;
		return crow::response(response);
	});

	// POST
	CROW_ROUTE(app, "/posts").methods("POST"_method)([](const crow::request &req) {
		auto json = crow::json::load(req.body);
		if (!json || !json.has("title") || !json.has("content") || !json.has("author_id")) {
			return crow::response(400, "Missing required fields: title, content, author_id");
		}

		// Check if author exists
		int authorId = json["author_id"].i();
		if (g_users.find(authorId) == g_users.end()) {
			return crow::response(400, "Author not found");
		}

		int id = ++g_post_id_count;
		g_posts[id] = Post(id, json["title"].s(), json["content"].s(), authorId);

		crow::json::wvalue response;
		response["id_"] = id;
		response["title_"] = json["title"].s();
		response["content_"] = json["content"].s();
		response["author_id_"] = authorId;
		return crow::response(response);
	});

	CROW_ROUTE(app, "/posts").methods("GET"_method)([]() {
		crow::json::wvalue postsArray;
		int i = 0;
		for (const auto &[id, post] : g_posts) {
			crow::json::wvalue postJson;
			postJson["id_"] = post.id_;
			postJson["title_"] = post.title_;
			postJson["content_"] = post.content_;
			postJson["author_id_"] = post.author_id_;
			postsArray[i++] = std::move(postJson);
		}
		return crow::response(postsArray);
	});

	CROW_ROUTE(app, "/posts/<int>").methods("GET"_method)([](int postId) {
		auto it = g_posts.find(postId);
		if (it == g_posts.end()) {
			return crow::response(404, "Post not found");
		}

		crow::json::wvalue response;
		response["id_"] = it->second.id_;
		response["title_"] = it->second.title_;
		response["content_"] = it->second.content_;
		response["author_id_"] = it->second.author_id_;
		return crow::response(response);
	});

	CROW_ROUTE(app, "/posts/<int>").methods("PUT"_method)([](const crow::request &req, int postId) {
		auto it = g_posts.find(postId);
		if (it == g_posts.end()) {
			return crow::response(404, "Post not found");
		}

		auto json = crow::json::load(req.body);
		if (!json) {
			return crow::response(400, "Invalid JSON");
		}

		if (json.has("title")) {
			it->second.title_ = json["title"].s();
		}
		if (json.has("content")) {
			it->second.content_ = json["content"].s();
		}
		if (json.has("author_id")) {
			int authorId = json["author_id"].i();
			if (g_users.find(authorId) == g_users.end()) {
				return crow::response(400, "Author not found");
			}
			it->second.author_id_ = authorId;
		}

		crow::json::wvalue response;
		response["id_"] = it->second.id_;
		response["title_"] = it->second.title_;
		response["content_"] = it->second.content_;
		response["author_id_"] = it->second.author_id_;
		return crow::response(response);
	});

	CROW_ROUTE(app, "/posts/<int>").methods("DELETE"_method)([](int postId) {
		auto it = g_posts.find(postId);
		if (it == g_posts.end()) {
			return crow::response(404, "Post not found");
		}

		g_posts.erase(it);
		return crow::response(204);
	});

	CROW_ROUTE(app, "/users/<int>/posts").methods("GET"_method)([](int userId) {
		if (g_users.find(userId) == g_users.end()) {
			return crow::response(404, "User not found");
		}

		crow::json::wvalue postsArray;
		int i = 0;
		for (const auto &[id, post] : g_posts) {
			if (post.author_id_ == userId) {
				crow::json::wvalue postJson;
				postJson["id_"] = post.id_;
				postJson["title_"] = post.title_;
				postJson["content_"] = post.content_;
				postJson["author_id_"] = post.author_id_;
				postsArray[i++] = std::move(postJson);
			}
		}
		return crow::response(postsArray);
	});

	// set the port, set the app to run on multiple threads, and run the app
	app.port(18080).multithreaded().run();
}