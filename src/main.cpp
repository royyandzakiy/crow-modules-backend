#include <crow.h>

import std;
import <unordered_map>;

import globals;
import user;
import post;
import user_routes;
import post_routes;

int main() {
	g_users.reserve(100);
	g_users.reserve(1000);

	std::println("Crow Start!");

	// PRE-LOAD INITIAL DATA EFFICIENTLY
	g_users.try_emplace(1, 1, "Alice Smith");
	g_users.try_emplace(2, 2, "Bob Johnson");
	g_users.try_emplace(3, 3, "Charlie Brown");
	g_user_id_count = 3;

	g_posts.try_emplace(101, 101, "Modern C++", "C++20/23 Features", 1);
	g_posts.try_emplace(102, 102, "Concurrency", "Threads and async", 2);
	g_posts.try_emplace(103, 103, "Modules", "C++20 Modules", 1);
	g_post_id_count = 103;

	// ROUTES
	user_routes_init();
	post_routes_init();

	// set the port, set the g_app to run on multiple threads, and run the g_app
	g_app.port(18080).multithreaded().run();
}