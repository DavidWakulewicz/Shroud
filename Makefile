#CLIENT
CLIENT_BUILD = Project1/build
CLIENT_SRC = Project1/src
CLIENT_BIN = Project1/bin

CLIENT_SRCS = StateManager.cpp Player.cpp World.cpp Keyboard.cpp Tile.cpp Camera.cpp Game.cpp Renderer.cpp Main.cpp
CLIENT_SRCS := $(CLIENT_SRCS:%.cpp=$(CLIENT_SRC)/%.cpp)

CLIENT_OBJS := $(CLIENT_SRCS:$(CLIENT_SRC)%.cpp=$(CLIENT_BUILD)%.o)

CLIENT_DEPDIR := .d

ifeq ($(OS),Windows_NT)
	RM = del /f

	CXX = clang++
	CPPFLAGS = -Wall -std=c++14 -I "Project1\include"
	LDFLAGS = -Wall -std=c++14 -L "Project1\lib"
	LDLIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

	CLIENT_SRCS := $(foreach src,$(CLIENT_SRCS),$(subst /src/,\src\,$(src)))
	CLIENT_OBJS := $(subst /,\,$(CLIENT_OBJS))
	CLIENT_BUILD := $(subst /,\,$(CLIENT_BUILD))
	CLIENT_SRC := $(subst /,\,$(CLIENT_SRC))
	CLIENT_BIN := $(subst /,\,$(CLIENT_BIN))
	CLIENT_BINARY = Shroud.exe
	CLIENT_BINARY_PATH = $(CLIENT_BIN)\$(CLIENT_BINARY)

	CLIENT_RUN_COMMAND = .\bin\$(CLIENT_BINARY)

	CLIENT_DEPFLAGS = -MT $@ -MMD -MP -MF $(CLIENT_DEPDIR)\$(basename $(notdir $*)).Td
	CLIENT_DEPDIR := $(subst /,\,$(CLIENT_DEPDIR))
	CLIENT_POSTCOMPILE = @move $(CLIENT_DEPDIR)\$(basename $(notdir $*)).Td $(CLIENT_DEPDIR)\$(basename $(notdir $*)).d
else
	RM = rm -f

	CXX = clang++
	CPPFLAGS = -Wall -std=c++14 -I "Project1/include"
	LDFLAGS = -Wall -std=c++14 -L "Project1/lib"
	LDLIBS = -lSDL2main -lSDL2 -lSDL2_image

	CLIENT_BINARY = Shroud
	CLIENT_BINARY_PATH = $(CLIENT_BIN)/$(CLIENT_BINARY)

	CLIENT_RUN_COMMAND = ./bin/$(CLIENT_BINARY)

	CLIENT_DEPFLAGS = -MT $@ -MMD -MP -MF $(CLIENT_DEPDIR)/$(basename $(notdir $*)).Td
	CLIENT_POSTCOMPILE = @mv $(CLIENT_DEPDIR)/$(basename $(notdir $*)).Td $(CLIENT_DEPDIR)/$(basename $(notdir $*)).d && touch $@
endif

.PHONY: windows linux clean

$(CLIENT_BUILD)\\%.o: $(CLIENT_SRC)\%.cpp
$(CLIENT_BUILD)\\%.o: $(CLIENT_SRC)\%.cpp $(CLIENT_DEPDIR)\%.d
	$(CXX) $(CLIENT_DEPFLAGS) $(CPPFLAGS) -o $@ -c $< -g -O0
	$(CLIENT_POSTCOMPILE)

$(CLIENT_BUILD)/%.o: $(CLIENT_SRC)/%.cpp
$(CLIENT_BUILD)/%.o: $(CLIENT_SRC)/%.cpp $(CLIENT_DEPDIR)/%.d
	$(CXX) $(CLIENT_DEPFLAGS) $(CPPFLAGS) -o $@ -c $< -g -O0
	$(CLIENT_POSTCOMPILE)


debug: $(CLIENT_OBJS)
	$(CXX) $(LDFLAGS) $(CLIENT_OBJS) $(LDLIBS) -g -O0 -o $(CLIENT_BINARY_PATH)

browser: $(CLIENT_SRCS)
	emcc $(CLIENT_SRCS) -s USE_SDL=2 -s DEMANGLE_SUPPORT=1 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file Project1/res@res -o main.js $(CPPFLAGS)

run:
	cd Project1 && $(CLIENT_RUN_COMMAND)

clean:
	$(RM) $(CLIENT_OBJS)

$(CLIENT_DEPDIR)/%.d: ;
$(CLIENT_DEPDIR)\\%.d: ;
.PRECIOUS: $(CLIENT_DEPDIR)\%.d $(CLIENT_DEPDIR)/%.d

include $(wildcard $(patsubst %,$(CLIENT_DEPDIR)/%.d,$(basename $(notdir $(CLIENT_SRCS)))))
