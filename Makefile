CC = clang
EXECUTABLE = endgame

# FOR UBUTNTU
CFLAGS = `sdl2-config --libs --cflags` -std=c11 -Wall -Wextra -Werror -Wpedantic -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm -g

# FOR ORACLE (MAC OS)
# CFLAGS = -std=c11 -Wall -Wextra -Wpedantic\
# 		 -framework SDL2_ttf \
# 	 	 -rpath resource/framework -framework SDL2 \
# 	 	 					  -framework SDL2_image \
# 	 	 					  -framework SDL2_mixer \
# 		-I resource/framework/SDL2_image.framework/Headers \
# 		-I resource/framework/SDL2_ttf.framework/Headers \
# 		-I resource/framework/SDL2_mixer.framework/Headers \
# 		-F resource/framework -I resource/framework/SDL2.framework/SDL2

SOURCES := $(wildcard src/*.c)
OBJECTS = $(addprefix obj/,$(notdir $(SOURCES:.c=.o)))

all: objdir $(SOURCES) $(EXECUTABLE)
	
objdir:
	mkdir -p obj

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

obj/%.o: src/%.c
	clang -std=c11 -Wall -Wextra -Werror -Wpedantic -g -c -o $@ $<
	
uninstall: clean
	rm -rf $(EXECUTABLE)

clean:

reinstall: uninstall all



NAME = endgame
 

# FOR UBUTNTU
# CFLAGS = `sdl2-config --libs --cflags` -std=c11 -Wall -Wextra -Werror -Wpedantic -lSDL2 -lSDL2_image -lSDL2_ttf -lm -g

# FOR ORACLE (MAC OS)
# CFLAGS = -std=c11 -Wall -Wextra -Wpedantic\
# 		 -framework SDL2_ttf \
# 	 	 -rpath resource/framework -framework SDL2 \
# 	 	 					  -framework SDL2_image \
# 	 	 					  -framework SDL2_mixer \
# 		-I resource/framework/SDL2_image.framework/Headers \
# 		-I resource/framework/SDL2_ttf.framework/Headers \
# 		-I resource/framework/SDL2_mixer.framework/Headers \
# 		-F resource/framework -I resource/framework/SDL2.framework/SDL2

# all: $(NAME) clean

# $(NAME) inc/*.h src/*.c:
# 	clang $(CFLAGS) src/*.c -o $(NAME)

# uninstall: clean
# 	rm -rf $(NAME)

# clean:

# reinstall: uninstall all

