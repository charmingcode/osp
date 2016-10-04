TOP_PATH=$(shell cd ../../../../ && pwd)
LDFLAGS=-L$(TOP_PATH)/build/osp_party/modules/lib -lstdc++ -lthrift -lssl -lcrypto
CPPFLAGS= $(LDFLAGS)\
					-I$(TOP_PATH)/build/osp_party/modules/include/\
					-I./gen-cpp/ \
					-I./

SOURCES_COMMON= gen-cpp/HttpApi.cpp\
								gen-cpp/httpapi_constants.cpp\
								gen-cpp/httpapi_types.cpp

SOURCES_CLIENT=CppClient.cpp

SOURCES_SERVER=CppServer.cpp

OBJECTS_COMMON = $(patsubst %.cpp,%.o,$(SOURCES_COMMON))
OBJECTS_CLIENT = $(patsubst %.cpp,%.o,$(SOURCES_CLIENT))
OBJECTS_SERVER = $(patsubst %.cpp,%.o,$(SOURCES_SERVER))

target:
	make CppClient
	make CppServer

%.o: %.cpp 
	gcc $(CPPFLAGS) $(CFLAGS) $< -c -o $@

CppClient:$(OBJECTS_CLIENT) $(OBJECTS_COMMON)
	gcc $(CPPFLAGS) $(CFLAGS) -o $@ $(OBJECTS_CLIENT) $(OBJECTS_COMMON)

CppServer:$(OBJECTS_SERVER) $(OBJECTS_COMMON)
	gcc $(CPPFLAGS) $(CFLAGS) -o $@ $(OBJECTS_SERVER) $(OBJECTS_COMMON)

clean:
	rm CppClient CppServer
	rm -rf *.o
	rm -rf ./gen-cpp/*.o
