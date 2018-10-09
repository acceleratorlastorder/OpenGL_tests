cmd /c "gcc main.c src/filesManagement/filesManager.c src/filesManagement/pictureManagement/getBmp_textures.c src/filesManagement/pictureManagement/pictureManagement.c src/vertexManagement/vertexs.c src/shadersManagement/shadersManager.c src/texturesManagement/texturesManagement.c src/objectManagement/opperation.c src/objectManagement/constructor.c src/physicsManagement/physics.c src/glad.c -DdebugBuild -lopengl32 -lcglm -lglfw3 -lkernel32 -luser32 -lgdi32 -lws2_32 -Wall -mtune=native -O3 -std=c11 -o test_5"

pause
