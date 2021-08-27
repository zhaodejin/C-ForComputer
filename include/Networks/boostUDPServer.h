//
// Created by 赵德金 on 2021/8/22.
//

#ifndef C_FORCOMPUTER_BOOSTUDP_H
#define C_FORCOMPUTER_BOOSTUDP_H
#include "utils/utils.h"
using namespace boost::asio;
void serveUDP()
{
    try{
        cout<<"UDP服务端开始...\n";
        io_service ios;
        ip::udp::socket sock(ios,ip::udp::endpoint(ip::udp::v4(),6699));

        while (1)
        {
            char buf[1];
            ip::udp::endpoint ep;
            boost::system::error_code ec;
            sock.receive_from(buffer(buf),ep,0,ec);

            if(ec&&ec!=error::message_size)
            {
                throw boost::system::system_error(ec);
            }
            cout<<"发送给："<<ep.address()<<endl;
            sock.send_to(buffer("你好，asio UPD"),ep);
        }
    }
    catch(std::exception& e)
    {
        cout<<e.what()<<endl;
    }
}
#endif //C_FORCOMPUTER_BOOSTUDP_H
