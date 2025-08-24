#pragma once

#include "../http/HttpResponse.h"
#include "../http/HttpRequest.h"

namespace http
{
    namespace router
    {
        class RouterHandler
        {
        public:
            virtual ~RouterHandler() = default;
            virtual void handle(const HttpRequest &req, HttpResponse *resp) = 0;
        };
    }
}