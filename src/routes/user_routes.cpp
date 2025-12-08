module;

#include <crow.h>

import std;

import globals;

export module user_routes;

export void user_routes_init() {
	CROW_ROUTE(g_app, "/")([]() {							 //
		auto page = crow::mustache::load_text("index.html"); //
		return page;										 //
	});

	// USERS
	CROW_ROUTE(g_app, "/users").methods("POST"_method)([](const crow::request &req) {
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

	CROW_ROUTE(g_app, "/users").methods("GET"_method)([]() {
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

	CROW_ROUTE(g_app, "/users/<int>").methods("GET"_method)([](int userId) {
		auto it = g_users.find(userId);
		if (it == g_users.end()) {
			return crow::response(404, "User not found");
		}

		crow::json::wvalue response;
		response["id"] = it->second.id_;
		response["name"] = it->second.name_;
		return crow::response(response);
	});

	CROW_ROUTE(g_app, "/users/<int>").methods("PUT"_method)([](const crow::request &req, int userId) {
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
}