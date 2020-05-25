cmake_minimum_required(VERSION 3.0)

set(GAME_NAME "minerGame")

project(${GAME_NAME})

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../")
set(INC_DIR "${SRC_DIR}/ENG/includes")
set(SOURCES
			# game source files
			# -----------------
			# main
			"${SRC_DIR}/${GAME_NAME}/main.cpp"
			# gameobjects
			"${SRC_DIR}/${GAME_NAME}/player.cpp"
			"${SRC_DIR}/${GAME_NAME}/asteroid.cpp"

			# engine source files
			# ------------------
			# shaders
			"${SRC_DIR}/ENG/shaders/shader.cpp"
			# objects
			"${SRC_DIR}/ENG/objects/game.cpp"
			"${SRC_DIR}/ENG/objects/gameobj.cpp"
			"${SRC_DIR}/ENG/objects/phyx.cpp"
			"${SRC_DIR}/ENG/objects/kldr.cpp"
			"${SRC_DIR}/ENG/objects/ctrl.cpp"
			"${SRC_DIR}/ENG/objects/rndr.cpp"
			"${SRC_DIR}/ENG/objects/sound.cpp"
			"${SRC_DIR}/ENG/objects/perlin.cpp"
			# camera
			"${SRC_DIR}/ENG/camera/camera.cpp"
			"${SRC_DIR}/ENG/camera/freecam.cpp"
			"${SRC_DIR}/ENG/camera/camOrt.cpp"
			"${SRC_DIR}/ENG/camera/cam3rd.cpp"
			# mesh
			"${SRC_DIR}/ENG/mesh/mesh.cpp"
			"${SRC_DIR}/ENG/mesh/cube.cpp"
			"${SRC_DIR}/ENG/mesh/sphere.cpp"
			# model
			"${SRC_DIR}/ENG/model/model.cpp"			

			# includes source files
			# ---------------------
			# glad
			"${INC_DIR}/glad/glad.c"
			# imgui
			"${INC_DIR}/imgui/imgui.cpp"
			"${INC_DIR}/imgui/imgui_impl_glfw.cpp"
			"${INC_DIR}/imgui/imgui_impl_opengl3.cpp"
			"${INC_DIR}/imgui/imgui_demo.cpp"
			"${INC_DIR}/imgui/imgui_draw.cpp"
			"${INC_DIR}/imgui/imgui_widgets.cpp"
			# stb_image
			"${INC_DIR}/stb_image/stb_image.cpp"

	)

add_subdirectory(${INC_DIR}/assimp assimp)

add_definitions(-DPWD="${SRC_DIR}")

add_executable(${PROJECT_NAME}.exe ${SOURCES})
target_include_directories(${PROJECT_NAME}.exe PRIVATE "${SRC_DIR}")
set_property(TARGET ${PROJECT_NAME}.exe PROPERTY CXX_STANDARD 17)

TARGET_LINK_LIBRARIES(${PROJECT_NAME}.exe assimp -lglfw -lGL -lX11 -lXrandr -ldl -lm -L"/usr/lib" "${INC_DIR}/IrrKlang/libIrrKlang.so" -lpthread)
