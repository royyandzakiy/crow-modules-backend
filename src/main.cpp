#include <crow.h>

import std;

int main()
{
	std::println("Crow Start!");
    crow::SimpleApp app; //define your crow application

    CROW_ROUTE(app, "/")([](){ // 
        auto page = crow::mustache::load_text("index.html"); // 
        return page; //
    });

    CROW_ROUTE(app, "/<string>")([](std::string name){ // 
        auto page = crow::mustache::load("index.html"); // 
        crow::mustache::context ctx ({{"person", name}}); // 
        return page.render(ctx); //
    });

    //set the port, set the app to run on multiple threads, and run the app
    app.port(18080).multithreaded().run();
}