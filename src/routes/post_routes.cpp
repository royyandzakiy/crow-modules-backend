module;

#include <crow.h>

import std;

import globals;

export module post_routes;

export void post_routes_init() {
	CROW_ROUTE(g_app, "/posts").methods("POST"_method)([](const crow::request &req) {
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

	CROW_ROUTE(g_app, "/posts").methods("GET"_method)([]() {
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

	CROW_ROUTE(g_app, "/posts/<int>").methods("GET"_method)([](int postId) {
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

	CROW_ROUTE(g_app, "/posts/<int>").methods("PUT"_method)([](const crow::request &req, int postId) {
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

	CROW_ROUTE(g_app, "/posts/<int>").methods("DELETE"_method)([](int postId) {
		auto it = g_posts.find(postId);
		if (it == g_posts.end()) {
			return crow::response(404, "Post not found");
		}

		g_posts.erase(it);
		return crow::response(204);
	});

	CROW_ROUTE(g_app, "/users/<int>/posts").methods("GET"_method)([](int userId) {
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
}