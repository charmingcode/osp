import sys
sys.path.append('gen-py')

from httpapi import HttpApi
from thrift.protocol import TBinaryProtocol 
from thrift.server import THttpServer


class HttpApiHandler:
  def __init__(self):
    self.m = {}

  def setKeyVal(self, k, v):
    print "set key=%s, val=%s"%(k,v)
    self.m[k] = v
    return True
  def getValByKey(self, k):
    return self.m.get(k, "null")

processor = HttpApi.Processor(HttpApiHandler())
protoFactory = TBinaryProtocol.TBinaryProtocolFactory()
port = 9090
server = THttpServer.THttpServer(processor, ("localhost", port), protoFactory)
print "Python server running on port " + str(port)
server.serve()

