#pragma once

#include "SessionStorage.h"
#include "../http/HttpRequest.h"
#include "../http/HttpResponse.h"
#include <memory>
#include <random>

namespace http
{
    namespace session
    {
        class SessionManager
        {
        public:
            explicit SessionManager(std::unique_ptr<SessionStorage> storage);

            std::shared_ptr<Session> getSession(const HttpRequest &req, HttpResponse *resp);

            void destroySession(const std::string &sessionId);
            void cleanExpiredSessions();
            void updateSession(std::shared_ptr<Session> session)
            {
                storage_->save(session);
            }

        private:
            std::string getSessionIdFromCookie(const HttpRequest &req);
            std::string generateSessionId();
            void setSessionCookie(const std::string &sessionId, HttpResponse *resq);

        private:
            std::unique_ptr<SessionStorage> storage_;
            std::mt19937 rng_;
        };
    }
}