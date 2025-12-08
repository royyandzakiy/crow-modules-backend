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

std::unordered_map<int, User> users;
std::unordered_map<int, Post> posts;
int g_user_id_count = 0;
int g_post_id_count = 0;

int main() {
	std::println("Crow Start!");

	crow::SimpleApp app; // define your crow application

	CROW_ROUTE(app, "/")([]() {								 //
		auto page = crow::mustache::load_text("index.html"); //
		return page;										 //
	});

	CROW_ROUTE(app, "/<string>")([](std::string name) {	 //
		auto page = crow::mustache::load("index.html");	 //
		crow::mustache::context ctx({{"person", name}}); //
		return page.render(ctx);						 //
	});

	// USERS
	CROW_ROUTE(app, "/users").methods("POST"_method)([](const crow::request &req) {
		auto json = crow::json::load(req.body);
		if (!json || !json.has("name")) {
			return crow::response(400, "Missing 'name' field");
		}

		int id = ++g_post_id_count;
		users[id] = User(id, json["name"].s());

		crow::json::wvalue response;
		response["id"] = id;
		response["name"] = json["name"].s();
		return crow::response(response);
	});

	// set the port, set the app to run on multiple threads, and run the app
	app.port(18080).multithreaded().run();
}