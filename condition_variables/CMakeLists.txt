cmake_minimum_required (VERSION 3.14)
project (condition_variable_sandbox)


add_executable ( sandbox
	source/cv.cpp
)

target_include_directories( sandbox
    PUBLIC
    include
)

target_compile_features( sandbox
	PRIVATE
	cxx_std_17
)
