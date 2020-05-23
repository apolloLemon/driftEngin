cmake_minimum_required(VERSION 3.0)

project(driftEngine)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../")
set(INC_DIR "${SRC_DIR}/ENG/includes")
set(SOURCES
			"${SRC_DIR}/minerGame/main.cpp"
			"${SRC_DIR}/minerGame/player.cpp"
			"${SRC_DIR}/minerGame/asteroid.cpp"

			"${SRC_DIR}/ENG/shaders/shader.cpp"
			
			"${SRC_DIR}/ENG/objects/game.cpp"
			"${SRC_DIR}/ENG/objects/gameobj.cpp"
			"${SRC_DIR}/ENG/objects/phyx.cpp"
			"${SRC_DIR}/ENG/objects/kldr.cpp"
			"${SRC_DIR}/ENG/objects/ctrl.cpp"
			"${SRC_DIR}/ENG/objects/rndr.cpp"
			"${SRC_DIR}/ENG/objects/sound.cpp"

			"${SRC_DIR}/ENG/camera/camera.cpp"
			"${SRC_DIR}/ENG/camera/freecam.cpp"
			"${SRC_DIR}/ENG/camera/camOrt.cpp"
			"${SRC_DIR}/ENG/camera/cam3rd.cpp"

			"${SRC_DIR}/ENG/mesh/mesh.cpp"
			"${SRC_DIR}/ENG/mesh/cube.cpp"
			"${SRC_DIR}/ENG/mesh/sphere.cpp"

			"${SRC_DIR}/ENG/model/model.cpp"			

			"${INC_DIR}/glad/glad.c"

			"${INC_DIR}/imgui/imgui.cpp"
			"${INC_DIR}/imgui/imgui_impl_glfw.cpp"
			"${INC_DIR}/imgui/imgui_impl_opengl3.cpp"
			"${INC_DIR}/imgui/imgui_demo.cpp"
			"${INC_DIR}/imgui/imgui_draw.cpp"
			"${INC_DIR}/imgui/imgui_widgets.cpp"

			"${INC_DIR}/stb_image/stb_image.cpp"

	)

add_subdirectory(${INC_DIR}/assimp assimp)

add_executable(${PROJECT_NAME}.exe ${SOURCES})
target_include_directories(${PROJECT_NAME}.exe PRIVATE "${SRC_DIR}")
set_property(TARGET ${PROJECT_NAME}.exe PROPERTY CXX_STANDARD 17)

TARGET_LINK_LIBRARIES(driftEngine.exe assimp -lglfw -lGL -lX11 -lXrandr -lXi -ldl -lGLU -lglut -lm -L"/usr/lib" "${INC_DIR}/IrrKlang/libIrrKlang.so" -lpthread)
