//
// Created by 赵德金 on 2021/8/22.
//

#ifndef C_FORCOMPUTER_BOOSTHTTP_H
#define C_FORCOMPUTER_BOOSTHTTP_H
#include "utils/utils.h"
//#define EXIT_FAILURE false
//#define EXIT_SUCCESS true
using tcp = boost::asio::ip::tcp;
namespace http = boost::beast::http;
int httpTest();
int httpTest()
{
    try {
        auto const host = "www.baidu.com";
        auto const port = "80";
        auto const target = "/";
        int version = 11;
        boost::asio::io_context ioc;
        tcp::resolver resolver{ioc};
        tcp::socket socket{ioc};
        auto const result = resolver.resolve(host,port);
        boost::asio::connect(socket,result.begin(),result.end());
        http::request<http::string_body> req{http::verb::get,target,version};
        req.set(http::field::host,host);
        req.set(http::field::user_agent,BOOST_BEAST_VERSION_STRING);
        http::write(socket,req);
        cout<<"正在写入中："<<endl;
        boost::beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        http::read(socket,buffer,res);
        cout<<"正在读入中："<<endl;
        cout<<"输出结果中："<<endl;
        cout<<res<<endl;
        boost::system::error_code ec;
        socket.shutdown(tcp::socket::shutdown_both,ec);
        if(ec&&ec != boost::system::errc::not_connected)
            throw boost::system::system_error{ec};

    }
    catch (std::exception const &e)
    {
        cerr<<"Error:"<<e.what()<<endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

#endif //C_FORCOMPUTER_BOOSTHTTP_H
