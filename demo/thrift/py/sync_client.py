import sys
import glob
sys.path.append('gen-py')
sys.path.insert(0, glob.glob('./lib/lib*')[0])

from httpapi import HttpApi
#from tutorial import Calculator
#from tutorial.ttypes import InvalidOperation, Operation, Work

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.transport import THttpClient
from thrift.protocol import TBinaryProtocol


def main():
    # Make socket
    transport = TSocket.TSocket('localhost', 9090)

    # Buffering is critical. Raw sockets are very slow
    # THttpClient vs tansport:THttpServerTransportFactory(cpp-async-test, now cpp async server only implement)
    # TBufferedTransport vs TBufferedTransport(cpp-sync-test)
    transport = THttpClient.THttpClient("http://127.0.0.1:9090/")
    #transport = TTransport.TBufferedTransport(transport)

    # Wrap in a protocol
    protocol = TBinaryProtocol.TBinaryProtocol(transport)

    # Create a client to use the protocol encoder
    client = HttpApi.Client(protocol)

    # Connect!
    transport.open()

    ret = client.setKeyVal("123","456")
    print('sek kv(123, 456) , ret =',ret)
  
    key = "abc"
    val = client.getValByKey(key)
    print(('get key %s, val=%s' % (key, val)))
    key = "123"
    val = client.getValByKey(key)
    print(('get key %s, val=%s' % (key, val)))

    # Close!
    transport.close()

if __name__ == "__main__":
  main()
