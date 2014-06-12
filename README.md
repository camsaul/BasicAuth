BasicAuth
=========

Basic HTTP authentication middleware for Crow

    #include "crow.h"
    #include "contrib/BasicAuth/BasicAuth.h"
    
    int main()
    {
        crow::Crow app;
    	
        CROW_ROUTE(app, "/")
        ([]{
            return "Hello World!";
        });
    
        CROW_MIDDLEWARE_USE(app, std::make_shared<crow_contrib::BasicAuth>("foo", "bar"));

        app.port(18080)
            .multithreaded()
            .run();
    }
