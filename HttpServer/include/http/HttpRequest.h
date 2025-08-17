#pragma once

#include <string>
#include <map>
#include <unordered_map>

#include <muduo/base/Timestamp.h>


namespace http
{
    class HttpRequest
    {
    public:
        enum Method
        {
            kInvalid,kGet,kPost,kHead,kPtu,kDelete,kOptions
        };

        HttpRequest()
        :method_(kInvalid)
        ,version_("Unknown")
        {}

        void setReceiveTime(muduo::Timestamp t);
        muduo::Timestamp receiveTime() const {return receiveTime_;}

        bool setMethod(const char* start,const char* end);
        Method method()const {return method_;}

        void setPath(const char* start,const char* end);
        std::string getPath()const {return path_;}

        void setPathParameters(const std::string &key,const std::string &value);
        std::string getPathParameters(const std::string &key) const;

        void setQueryParameters(const char* start,const char* end);
        std::string getQueryParameters(const std::string& key)const;

        void setVersion(std::string v)
        {
            version_=v;
        }

        std::string getVersion()const
        {
            return version_;
        }

        void addHeader(const char* start,const char* colon,const char* end);
        std::string getHeader(const std::string& field)const;

        const std::map<std::string,std::string>& headers()const
        {return headers_;}

        void setBody(const std::string& body){content_=body;}
        void setBody(const char* start,const char* end)
        {
            if(end>=start)
            {
                content_.assign(start,end-start);
            }
        }    

        std::string getBody()const
        {return content_;}

        void setContentLength(uint64_t length)
        {contentLength_=length;}

        uint64_t contentLength()const
        {return contentLength_;}

        void swap(HttpRequest& that);

    private:
        Method  method_;
        std::string version_;
        std::string path_;
        std::unordered_map<std::string ,std::string>    pathParameters_;
        std::unordered_map<std::string,std::string>     queryParameters_;
        muduo::Timestamp    receiveTime_;
        std::map<std::string,std::string>   headers_;
        std::string     content_;
        uint64_t    contentLength_ {0};
    };
}