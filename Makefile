#CLIENT
CLIENT_BUILD = Project1/build
CLIENT_SRC = Project1/src

CLIENT_SRCS = main.cpp Game.cpp Renderer.cpp
CLIENT_SRCS := $(CLIENT_SRCS:%.cpp=$(CLIENT_SRC)/%.cpp)

CLIENT_OBJS := $(CLIENT_SRCS:$(CLIENT_SRC)%.cpp=$(CLIENT_BUILD)%.o)

CLIENT_DEPDIR := .d
CLIENT_DEPFLAGS = -MT $@ -MMD -MP -MF $(CLIENT_DEPDIR)\$(basename $(notdir $*)).Td
CLIENT_POSTCOMPILE = @move $(CLIENT_DEPDIR)\$(basename $(notdir $*)).Td $(CLIENT_DEPDIR)\$(basename $(notdir $*)).d

ifeq ($(OS),Windows_NT)
	RM = del /f

	CXX = clang++
	CPPFLAGS = -std=c++14 -I "Project1\include"
	LDFLAGS = -std=c++14 -L "Project1\lib"
	LDLIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

	CLIENT_SRCS := $(foreach src,$(CLIENT_SRCS),$(subst /src/,\src\,$(src)))
	CLIENT_OBJS := $(subst /,\,$(CLIENT_OBJS))
	CLIENT_BUILD := $(subst /,\,$(CLIENT_BUILD))
	CLIENT_SRC := $(subst /,\,$(CLIENT_SRC))

	CLIENT_DEPDIR := $(subst /,\,$(CLIENT_DEPDIR))
else
	RM = rm -f

	CXX = clang++
	CPPFLAGS = -std=c++14 -I "Project1/include"
	LDFLAGS = -std=c++14 -L "Project1/lib"
	LDLIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
endif

.PHONY: windows clean

$(CLIENT_BUILD)\\%.o: $(CLIENT_SRC)\%.cpp
$(CLIENT_BUILD)\\%.o: $(CLIENT_SRC)\%.cpp $(CLIENT_DEPDIR)\%.d
	$(CXX) $(CLIENT_DEPFLAGS) $(CPPFLAGS) -o $@ -c $<
	$(CLIENT_POSTCOMPILE)

windows: $(CLIENT_OBJS)
	$(CXX) $(LDFLAGS) $(CLIENT_OBJS) -g -o Project1/bin/Shroud.exe $(LDLIBS)

run:
	cd Project1 && .\bin\Shroud.exe

clean:
	$(RM) $(CLIENT_OBJS)
	$(RM) $(SERVER_OBJS)

$(CLIENT_DEPDIR)\\%.d: ;
.PRECIOUS: $(CLIENT_DEPDIR)\%.d

include $(wildcard $(patsubst %,$(CLIENT_DEPDIR)/%.d,$(basename $(notdir $(CLIENT_SRCS)))))
