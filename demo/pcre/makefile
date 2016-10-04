TARGET=pcre_test
TOP_PATH=$(shell cd ../../ && pwd)

LDFLAGS= -g

LIBS += \
				-L$(TOP_PATH)/build/osp_party/modules/lib\
				-lstdc++\
				-lpcre

INCLUDES = \
				-I$(TOP_PATH)/build/osp_party/modules/include/
						

CPPFLAGS= $(LDFLAGS)\
					$(INCLUDES)\
					$(LIBS)\
					$(LDFLAGS)

SOURCES=main.cpp

OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))
%.o: %.cpp 
	gcc $(CPPFLAGS) $< -c -o $@

$(TARGET):$(OBJECTS)
	gcc $(CPPFLAGS) -o $@ $(OBJECTS)

clean:
	rm -rf $(TARGET) $(OBJECTS)
