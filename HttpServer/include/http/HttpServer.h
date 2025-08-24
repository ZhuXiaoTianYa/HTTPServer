#pragma once

#include <functional>
#include <memory>
#include <map>

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/base/Logging.h>

#include "HttpContext.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "../router/Router.h"
#include "../session/SessionManager.h"
#include "../ssl/SslConnection.h"
#include "../middleware/Mid d lewareChain.h"
#include 
namespace http
{
    class HttpServer : muduo::noncopyable
    {
    public:
        using HttpCallback = std::function<void(const http::HttpRequest &, http::HttpResponse *)>;

    public:
        HttpServer(int port, const std::string &name, bool useSSL = false, muduo::net::TcpServer::Option option = muduo::net::TcpServer::kNoReusePort);

        void setThreadNum(int numThreads)
        {
            server_.setThreadNum(numThreads);
        }

        void start();

        muduo::net::EventLoop* getLoop()const
        {
            return server_.getLoop();
        }

        void setHttpCallback(const HttpCallback& cb)
        {
            httpCallback_ = cb;
        }

        void Get(const std::string& path,const HttpCallback& cb)
        {
            
        }

    private:
        void handleRequest(const HttpRequest &req, HttpResponse *resp);

        void initialize();

        void onConnection(const muduo::net::TcpConnectionPtr &conn);
        void onMessage(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer *buf, muduo::Timestamp receiveTime);

    private:
        muduo::net::InetAddress listenAddr_;
        muduo::net::TcpServer server_;
        muduo::net::EventLoop mainLoop_;
        HttpCallback httpCallback_;
        router::Router router_;
        std::unique_ptr<session::SessionManager> sessionManager_;
        middleware::MiddlewareChain middlewareChain_;
        std::unique_ptr<ssl::SslContext> sslCtx_;
        bool useSSL_;
        std::map<muduo::net::TcpConnectionPtr, std::unique_ptr<ssl::SslConnection>> sslConns_;
    };
}