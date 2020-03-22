COMPILER = gcc
EXEC_NAME = learning_8
ARCHFLAGS = -march=znver1
LANG_VERSION = -std=c11
OPTI_lEVEL = -O3
LIBS = -lopengl32 -lcglm -lglfw3 -lkernel32 -luser32 -lgdi32 -lws2_32
VARIABLES = -DdebugBuild
CFLAGS = $(VARIABLES) $(LIBS) -Wall -mtune=native $(LANG_VERSION) $(OPTI_lEVEL) $(ARCHFLAGS) -o $(EXEC_NAME)


CLEAN_TARGET = *.o
ifeq ($(OS),Windows_NT)
    EXTENSION=.exe
    RM = del /Q /F
    RRM = rmdir /Q /S
else
    RM = rm -f
    RRM = rm -rf
endif

OBJECTS = filesManager.o getBmp_textures.o pictureManagement.o \
				vertexs.o shadersManager.o texturesManagement.o \
				opperation.o constructor.o physics.o glad.o main.o

all: compile
		@echo "Compiling Project"/proc/cpuinfo

compile: main.o

		@echo "Compiling Project"
		$(COMPILER) $(OBJECTS) $(CFLAGS)

compact:
		@echo "Compact mode used (might be the perf focused build, need later bench to prove this)"
		$(COMPILER) main.c src/filesManagement/filesManager.c \
		src/filesManagement/pictureManagement/getBmp_textures.c \
		src/filesManagement/pictureManagement/pictureManagement.c \
		src/vertexManagement/vertexs.c \
		src/shadersManagement/shadersManager.c \
		src/texturesManagement/texturesManagement.c \
		src/objectManagement/opperation.c \
		src/objectManagement/constructor.c \
		src/physicsManagement/physics.c \
		src/glad.c \
		$(CFLAGS)

main.o: filesManager.o getBmp_textures.o pictureManagement.o \
				vertexs.o shadersManager.o texturesManagement.o \
				opperation.o constructor.o physics.o glad.o
	$(COMPILER) -o main.o -c main.c
filesManager.o:
	@echo "Compiling filesManager"
	$(COMPILER) -o filesManager.o -c src/filesManagement/filesManager.c

getBmp_textures.o:
	@echo "Compiling getBmp_textures"
	$(COMPILER) -o getBmp_textures.o -c src/filesManagement/pictureManagement/getBmp_textures.c

pictureManagement.o:
	@echo "Compiling pictureManagement"
	$(COMPILER) -o pictureManagement.o -c src/filesManagement/pictureManagement/pictureManagement.c

vertexs.o:
	@echo "Compiling vertexs"
	$(COMPILER) -o vertexs.o -c src/vertexManagement/vertexs.c

shadersManager.o: glad.o
	@echo "Compiling shadersManager"
	$(COMPILER) -o shadersManager.o -c src/shadersManagement/shadersManager.c -lcglm -lglfw3

texturesManagement.o:
	@echo "Compiling texturesManagement"
	$(COMPILER) -o texturesManagement.o -c src/texturesManagement/texturesManagement.c

opperation.o:
	@echo "Compiling opperation"
	$(COMPILER) -o opperation.o -c src/objectManagement/opperation.c

constructor.o:
	@echo "Compiling constructor"
	$(COMPILER) -o constructor.o -c src/objectManagement/constructor.c

physics.o:
	@echo "Compiling physics"
	$(COMPILER) -o physics.o -c src/physicsManagement/physics.c

glad.o:
	@echo "Compiling glad"
	$(COMPILER) -o glad.o -c src/glad.c

clean: clean_exec
	@echo "clean project"
	$(RM) $(CLEAN_TARGET)
	@echo "clean completed"

clean_exec:
	$(RM) $(EXEC_NAME)$(EXTENSION)
