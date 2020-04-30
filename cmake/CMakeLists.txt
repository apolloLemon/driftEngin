cmake_minimum_required(VERSION 3.0)

project(driftEngine)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../")
set(INC_DIR "${SRC_DIR}/includes")
set(SOURCES "${SRC_DIR}/main.cpp"
			"${SRC_DIR}/init.cpp"
			"${SRC_DIR}/glad.c"

			"${SRC_DIR}/camera/camera.cpp"
			"${SRC_DIR}/camera/freecam.cpp"
			"${SRC_DIR}/camera/cam3rd.cpp"
			"${SRC_DIR}/camera/camOrt.cpp"

			"${SRC_DIR}/meshes/sphere.cpp"
			"${SRC_DIR}/meshes/cube.cpp"
			"${SRC_DIR}/meshes/plane.cpp"
			"${SRC_DIR}/meshes/mesh.cpp"

			"${SRC_DIR}/textures/texture.cpp"
			"${SRC_DIR}/shaders/shader.cpp"

			"${INC_DIR}/stb_image/stb_image.cpp"
	)

add_executable(${PROJECT_NAME}.exe ${SOURCES})
target_include_directories(${PROJECT_NAME}.exe PRIVATE "${SRC_DIR}")
set_property(TARGET ${PROJECT_NAME}.exe PROPERTY CXX_STANDARD 11)

TARGET_LINK_LIBRARIES(driftEngine.exe -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lGLU -lglut -lm)
