//
// Created by wunl on 18-8-5.
//

#ifndef ENCODER_HTTPSERVER_H
#define ENCODER_HTTPSERVER_H

#include <muduo/net/http/HttpServer.h>
#include <muduo/net/http/HttpRequest.h>
#include <muduo/net/http/HttpResponse.h>
#include <muduo/net/EventLoop.h>
#include <muduo/base/Logging.h>

#include <iostream>
#include <memory>
#include <utility>

//#include <boost/any.hpp>
#include <boost/utility.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <string>

class encoder;

class httpServer : public boost::noncopyable
{
public:
    /// \brief
    /// \param port
    /// \param numThreads
    httpServer(int port, int numThreads);

    /// \brief
    void start();

    httpServer();

private:
    /// \brief 1234
    /// \param req 45
    /// \param resp
    void onRequest(const muduo::net::HttpRequest &req, muduo::net::HttpResponse *resp);

protected:

private:
//    std::vector<std::unique_ptr<encoder> > encoderVec_;
    /// \brief 的的的
    muduo::net::EventLoop loop;
    std::unique_ptr<muduo::net::HttpServer> muduoHttpServer_;
};


#endif //ENCODER_HTTPSERVER_H
