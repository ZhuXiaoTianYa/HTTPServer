#pragma once

#include "../Middleware.h"
#include "../../http/HttpRequest.h"
#include "../../http/HttpResponse.h"
#include "CorsConfig.h"

namespace http
{
    namespace middleware
    {
        class CorsMiddleware : public Middleware
        {
        public:
            explicit CorsMiddleware(const CorsConfig &config = CorsConfig::defaultConfig());

            void before(HttpRequest &request) override;
            void after(HttpResponse &response) override;

            std::string join(const std::vector<std::string> &strings, const std::string &delimiter);

        private:
            void handlePreflightRequest(const HttpRequest &request, HttpResponse &response);
            bool isOriginAllowed(const std::string &origin) const;
            void addCorsHeaders(HttpResponse &response, const std::string &origin);

        private:
            CorsConfig config_;
        };
    }
}