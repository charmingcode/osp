var thrift = require('thrift');                   

//var ThriftTransports = require('thrift/transport');
//var ThriftProtocols = require('thrift/protocol');
var assert = require('assert');


var HttpApi = require('./gen-nodejs/HttpApi');
var ttypes = require('./gen-nodejs/httpapi_types.js');

var options = {
   transport: thrift.TBufferedTransport,
   protocol: thrift.TBinaryProtocol,
   http: true,
   path: "/",
   headers: {"Connection": "close"},
   https: false
};

function clientFactory(options){
    if(options.http){
        var connection = thrift.createHttpConnection("localhost", 9090, options);
        connection.on('error', function(err) {
          assert(false, err);
        });
        return thrift.createHttpClient(HttpApi, connection);

    } else {
        var connection = thrift.createConnection("127.0.0.1", 9090, options);
        connection.on('error', function(err) {
          assert(false, err);
        });
        // Create a client with the connection
        return thrift.createClient(HttpApi, connection);

    }
}

var client = clientFactory(options);

/*
*/
client.setKeyVal("abc","123", function(err, response) {
  console.log("setKeyVal(abc) = 123, callback response =" + response);
});

client.getValByKey("abc", function(err, response) {
  console.log("getValByKey(abc)  =" + response);
});
client.getValByKey("abcd", function(err, response) {
  console.log("getValByKey(abcd)  =" + response);
});
console.log("come here")

