#include <iostream>
#include "event.h"

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/async/TEvhttpClientChannel.h>

#include "./gen-cpp/HttpApi.h"
#include <boost/bind.hpp>
#include <boost/function.hpp>

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace ::apache::thrift::async;
using namespace HttpApi;
using namespace ::boost;
using ::boost::bind;

void my_setKeyVal(HttpApiCobClient* client)
{
    bool ret = client->recv_setKeyVal();
    printf("[%d] setKeyVal:%d\n", (int)time(NULL), ret);
}

int main(int argc, char **argv) {
  try{
    event_base* evbase = event_base_new();
    boost::shared_ptr<TAsyncChannel> channel(new TEvhttpClientChannel("127.0.0.1", "/", "127.0.0.1", 9090, evbase));
    HttpApiCobClient client(channel, new TBinaryProtocolFactory());
    function<void(HttpApiCobClient* client)> cob = bind(&my_setKeyVal,_1);
    
    cout<<"tansport:TEvhttpClientChannel"<<endl;
    cout<<"protocol:TBinaryProtocolFactory"<<endl;

    std::string key = "123";
    std::string val = "abc";
    client.setKeyVal(cob, key, val);
    printf("[%d] setKeyVal begin\n", (int)time(NULL));

    /*
    for(int i=0;i<5;i++)
    {
      printf("[%d] running...\n", (int)time(NULL));
      sleep(1);
    }
    */
    event_base_dispatch(evbase);
    event_base_free(evbase);
  }

  catch(...)
  {
    printf("exception");
    return 1;
  }

  return 0;
};
