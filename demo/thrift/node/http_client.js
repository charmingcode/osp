var thrift = require('thrift');
var HttpApi = require('./gen-nodejs/HttpApi');
var ttypes = require('./gen-nodejs/httpapi_types.js');

var options = {
   transport: thrift.TBufferedTransport,
   protocol: thrift.TBinaryProtocol,
   path: "/",
   headers: {"Connection": "close"},
   https: false
};

var connection = thrift.createHttpConnection("localhost", 9090, options);
var client = thrift.createHttpClient(HttpApi, connection);

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

