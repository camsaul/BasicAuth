#pragma once

#include "../../crow.h"
#include "base64.h"

namespace crow_contrib
{
	class BasicAuth : public crow::IMiddlewareHandler {

    private:
        string m_serverAuthString;
        string m_realm;

        bool passAuth(const string authHeader) {
            return authHeader.length() == m_serverAuthString.length() && authHeader == m_serverAuthString;
        }

    public:

        BasicAuth(const string username, const string password, const string realm = "Authorization Required")
        :   m_realm (realm)
         {
                string unencodedUserPass = username + ":" + password;
                int resultLen = 0;
                string encodedUserPass = base64(unencodedUserPass.c_str(), unencodedUserPass.length(), &resultLen);
                m_serverAuthString = string("Basic ") + encodedUserPass; 
            }

        crow::response handle(const crow::request& req, crow::Middleware::Context *c) override {
            if(!req.headers.count("authorization") || !passAuth(req.headers.at("authorization")) ){
                crow::response resp(401);
                resp.headers["WWW-Authenticate"] = "Basic realm=\""+m_realm+"\"";
                return resp;
            }
            return c->next();
        }
	};
}