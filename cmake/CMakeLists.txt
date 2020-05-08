cmake_minimum_required(VERSION 3.0)

project(driftEngine)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../")
set(INC_DIR "${SRC_DIR}/includes")
set(SOURCES "${SRC_DIR}/main.cpp"
			"${SRC_DIR}/init.cpp"
			"${SRC_DIR}/glad.c"
			
			"${SRC_DIR}/utilities/perlin.cpp"
			"${SRC_DIR}/utilities/phyx.cpp"

			"${SRC_DIR}/imgui/imgui.cpp"
			"${SRC_DIR}/imgui/imgui_demo.cpp"
			"${SRC_DIR}/imgui/imgui_draw.cpp"
			"${SRC_DIR}/imgui/imgui_impl_glfw.cpp"
			"${SRC_DIR}/imgui/imgui_impl_opengl3.cpp"
			"${SRC_DIR}/imgui/imgui_widgets.cpp"

			"${SRC_DIR}/gameobjects/gameObj.cpp"

			"${SRC_DIR}/mesh/mesh.cpp"
			"${SRC_DIR}/mesh/model.cpp"
			"${SRC_DIR}/mesh/cube.cpp"
			"${SRC_DIR}/mesh/sphere.cpp"

			"${SRC_DIR}/camera/camera.cpp"
			"${SRC_DIR}/camera/freecam.cpp"
			"${SRC_DIR}/camera/cam3rd.cpp"
			"${SRC_DIR}/camera/camOrt.cpp"

			#"${SRC_DIR}/player.cpp"

			"${SRC_DIR}/shaders/shader.cpp"

			"${INC_DIR}/stb_image/stb_image.cpp"
	)

add_subdirectory(${INC_DIR}/assimp assimp)

add_executable(${PROJECT_NAME}.exe ${SOURCES})
target_include_directories(${PROJECT_NAME}.exe PRIVATE "${SRC_DIR}")
set_property(TARGET ${PROJECT_NAME}.exe PROPERTY CXX_STANDARD 17)

TARGET_LINK_LIBRARIES(driftEngine.exe assimp -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lGLU -lglut -lm)
