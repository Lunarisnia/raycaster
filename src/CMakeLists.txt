# collect all imgui files
# file(GLOB SOURCES vendor/imgui/*.cpp)

# Add the source files
add_executable(${PROJECT_NAME} 
	main.cpp 

	# core/shader/shader.cpp

	# Imgui
	# ${SOURCES}
	# vendor/imgui/backends/imgui_impl_opengl3.cpp
	# vendor/imgui/backends/imgui_impl_glfw.cpp
	# vendor/imgui/misc/cpp/imgui_stdlib.cpp
)

# inlcude
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
# imgui include
# target_include_directories(${PROJECT_NAME} PUBLIC vendor/imgui)

# Link to vendor
target_link_libraries(${PROJECT_NAME} vendor)
