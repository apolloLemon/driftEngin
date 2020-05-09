cmake_minimum_required(VERSION 3.0)

project(driftEngine)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../")
set(INC_DIR "${SRC_DIR}/includes")
set(SOURCES
			"${SRC_DIR}/main.cpp"
			"${SRC_DIR}/init.cpp"

			"${SRC_DIR}/shaders/shader.cpp"

			"${SRC_DIR}/objects/gameObj.cpp"
			"${SRC_DIR}/objects/phyxObj.cpp"
			"${SRC_DIR}/objects/collisionObj.cpp"
			"${SRC_DIR}/objects/inputObj.cpp"
			"${SRC_DIR}/objects/renderObj.cpp"

			"${SRC_DIR}/actors/camera/camera.cpp"
			"${SRC_DIR}/actors/camera/freecam.cpp"
			"${SRC_DIR}/actors/camera/camOrt.cpp"
			"${SRC_DIR}/actors/player.cpp"

			"${SRC_DIR}/mesh/mesh.cpp"
			"${SRC_DIR}/mesh/cube.cpp"
			"${SRC_DIR}/mesh/sphere.cpp"

			"${SRC_DIR}/model/model.cpp"			

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

TARGET_LINK_LIBRARIES(driftEngine.exe assimp -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lGLU -lglut -lm)
