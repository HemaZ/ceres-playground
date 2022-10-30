add_executable(HelloWorld 01-HelloWorld.cpp)
target_link_libraries(HelloWorld ${CONAN_LIBS})

add_executable(CurveFitting 02-CurveFitting.cpp)
target_link_libraries(CurveFitting ${CONAN_LIBS})