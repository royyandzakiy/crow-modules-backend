module;

#include <crow.h>

import std;
import <unordered_map>;

import user;
import post;

export module globals;

export std::unordered_map<int, User> g_users;
export std::unordered_map<int, Post> g_posts;
export int g_user_id_count = 0;
export int g_post_id_count = 0;
export crow::SimpleApp g_app;