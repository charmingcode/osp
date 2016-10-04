var thrift = require('thrift');                   
var svc = require('./gen-nodejs/HttpApi');
var dict = {}
//ServiceHandler: Implement the hello service 
var svchandler = {
  setKeyVal: function (k, v, result) {
    console.log("Received setKeyVal call",k,v);
    dict[k]=v;
    result(null, 1);
  },
  getValByKey: function (k, result) {
    console.log("Received getValByKey call");
    if(dict.hasOwnProperty(k)){
      result(null, dict[k]);
    } else {
      result(null, "");
    }
  }
};

//ServiceOptions: The I/O stack for the service
var svcOpt = {                           
    handler: svchandler,                        
    processor: svc,                          
    protocol: thrift.TBinaryProtocol,                 
    transport: thrift.TBufferedTransport    
    //transport: thrift.TFramedTransport    
};                                  

//ServerOptions: Define server features
var serverOpt = {                           
   services: {                         
      "/": svcOpt                 
   }                               
}                                   

//Create and start the web server 
var port = 9090;                                
thrift.createWebServer(serverOpt).listen(port);                           
console.log("Http/Thrift Server running on port: " + port);


