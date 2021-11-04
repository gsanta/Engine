CC=emcc
SOURCES=main.cpp src\ShaderProgramImpl.cpp src\Camera.cpp src\shapes\Cube.cpp src\rendering\Renderer.cpp
SOURCES+=src\shapes\Shape.cpp
SOURCES+=src\rendering\Proj.cpp
SOURCES+=src\rendering\Perspective.cpp
SOURCES+=src\shapes\Pyramid.cpp
# .\src\ShaderProgram.cpp .\src\Camera.cpp .\src\shapes\Cube.cpp .\src\rendering\Renderer.cpp
# SOURCES+=~/ParseEnum.cpp
LDFLAGS=-O2 --llvm-opts 2
CFLAGS=-std=c++11  -s USE_SDL=2 -s -IC:\apps\opengl\include -O3
EMCC_DEBUG=1

# all: $(SOURCES) $(OUTPUT)

index.js: $(SOURCES) 
	$(CC) $^ $(CFLAGS) -o $@ 
# 	$(CC) $(SOURCES) -std=c++11  -s USE_SDL=2 -s -IC:\apps\opengl\include -O3 -o $(OUTPUT)

clean:
	rm index.js