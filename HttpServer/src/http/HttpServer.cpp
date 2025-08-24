#include "../../include/http/HttpServer.h"

namespace http
{
    HttpServer::HttpServer(int port, const std::string &name, bool useSSL, muduo::net::TcpServer::Option option)
        : listenAddr_(port), server_(&mainLoop_, listenAddr_, name, option), useSSL_(useSSL), httpCallback_(std::bind(&HttpServer::handleRequest, this, std::placeholders::_1, std::placeholders::_2))
    {
        initialize();
    }

    void HttpServer::start()
    {
        LOG_WARN << "HttpServer[" << server_.name() << "] starts listening on " << server_.ipPort();
        server_.start();
        mainLoop_.loop();
    }

    void HttpServer::initialize()
    {
        server_.setConnectionCallback(std::bind(&HttpServer::onConnection, this, std::placeholders::_1));
        server_.setMessageCallback(std::bind(&HttpServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    }
}