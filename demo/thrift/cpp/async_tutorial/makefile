TOP_PATH=$(shell cd ../../../../ && pwd)
LDFLAGS=-L$(TOP_PATH)/build/osp_party/modules/lib -lstdc++ -lssl -lcrypto -levent -lthriftnb -lthrift
CPPFLAGS= $(LDFLAGS)\
					-I$(TOP_PATH)/build/osp_party/modules/include/\
					-I./gen-cpp/ \
					-I./

SOURCES_COMMON_COB = ./gen-cpp/HttpApi.cpp \
										 ./gen-cpp/httpapi_constants.cpp \
										 ./gen-cpp/httpapi_types.cpp	
						

SOURCES_CLIENT_COB=CppCobClient.cpp

SOURCES_SERVER_COB=CppCobServer.cpp

OBJECTS_COMMON_COB = $(patsubst %.cpp,%.o,$(SOURCES_COMMON_COB))
OBJECTS_CLIENT_COB = $(patsubst %.cpp,%.o,$(SOURCES_CLIENT_COB))
OBJECTS_SERVER_COB = $(patsubst %.cpp,%.o,$(SOURCES_SERVER_COB))

target:
	make CppCobServer
	make CppCobClient

%.o: %.cpp 
	gcc $(CPPFLAGS) $(CFLAGS) $< -c -o $@

CppCobServer:$(OBJECTS_SERVER_COB) $(OBJECTS_COMMON_COB)
	gcc $(CPPFLAGS) $(CFLAGS) -o $@ $(OBJECTS_SERVER_COB) $(OBJECTS_COMMON_COB)

CppCobClient:$(OBJECTS_CLIENT_COB) $(OBJECTS_COMMON_COB)
	gcc $(CPPFLAGS) $(CFLAGS) -o $@ $(OBJECTS_CLIENT_COB) $(OBJECTS_COMMON_COB)

clean:
	rm CppCobClient CppCobServer
	rm -rf *.o
	rm -rf ./gen-cpp/*.o
