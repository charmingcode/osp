/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/THttpServer.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/TToString.h>
#include <thrift/async/TEvhttpClientChannel.h>

#include <iostream>
#include <stdexcept>
#include <sstream>

#include "./gen-cpp/HttpApi.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;
using namespace ::apache::thrift::async;

using namespace HttpApi;

class HttpApiHandler : public HttpApiIf {
 public:
  HttpApiHandler() { cout<<"ctor call"<<endl;}
  ~HttpApiHandler() { cout<<"dtor call"<<endl;}

  bool setKeyVal(const std::string& key, const std::string& val) {
    datastore_[key] = val;
    cout<<"[CppServer.cpp]setKeyVal "<<key<<" = "<<val<<endl;
    return true;
  }

  void getValByKey(std::string& _return, const std::string& key) {
    std::map<std::string, std::string>::iterator it = datastore_.find(key);
    if (it != datastore_.end()) {
         _return = it->second;
         return;
    } 
    _return = "";
  }

 private:
  std::map<std::string, std::string> datastore_;
};

int main(int argc, char **argv) {
  
  int port = 9090;
  boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
  boost::shared_ptr<HttpApiHandler> handler(new HttpApiHandler());
  boost::shared_ptr<TProcessor> processor(new HttpApiProcessor(handler));
  boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  //boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  boost::shared_ptr<TTransportFactory> transportFactory(new THttpServerTransportFactory());

  TSimpleServer server(processor,
                       serverTransport,
                       transportFactory,
                       protocolFactory);

  cout<<"tansport:THttpServerTransportFactory"<<endl;
  cout<<"protocol:TBinaryProtocolFactory"<<endl;

  /**
   * Or you could do one of these

  const int workerCount = 4;

  boost::shared_ptr<ThreadManager> threadManager =
    ThreadManager::newSimpleThreadManager(workerCount);
  boost::shared_ptr<PosixThreadFactory> threadFactory =
    boost::shared_ptr<PosixThreadFactory>(new PosixThreadFactory());
  threadManager->threadFactory(threadFactory);
  threadManager->start();
  TThreadPoolServer server(processor,
                           serverTransport,
                           transportFactory,
                           protocolFactory,
                           threadManager);

  TThreadedServer server(processor,
                         serverTransport,
                         transportFactory,
                         protocolFactory);

  */

  cout << "Starting the server[port:"<<port<<"]..." << endl;
  server.serve();
  cout << "Done." << endl;
  return 0;
}
