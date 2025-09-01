#include "../../include/middleware/MiddlewareChain.h"
#include <muduo/base/Logging.h>

namespace http
{
    namespace middleware
    {
        void MiddlewareChain::addMiddleware(std::shared_ptr<Middleware> middleware)
        {
            middlewares_.push_back(middleware);
        }

        void MiddlewareChain::processBefore(HttpRequest &request)
        {
            for (auto &middleware : middlewares_)
            {
                middleware->before(request);
            }
        }

        void MiddlewareChain::processAfter(HttpResponse &response)
        {
            try
            {
                for (auto it = middlewares_.rbegin(); it != middlewares_.rend(); ++it)
                {
                    if (*it)
                    {
                        (*it)->after(response);
                    }
                }
            }
            catch (const std::exception &e)
            {
                LOG_ERROR << "Error in middleware after processing: " << e.what();
            }
        }
    }
}