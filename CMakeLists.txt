cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
set(PROJECT_NAME SmartPulpit)
project(${PROJECT_NAME})# LANGUAGES CXX CUDA)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


# Qt5
find_package(Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(X11 COMPONENTS X11 Xft)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

# OpenCV
find_package(OpenCV REQUIRED)

find_package(CUDA)
message("-- CUDA version: ${CUDA_VERSION}")

set(
	CUDA_NVCC_FLAGS
	${CUDA_NVCC_FLAGS}; 
    -O3 
	-gencode arch=compute_53,code=sm_53
	-gencode arch=compute_62,code=sm_62
)

if(CUDA_VERSION_MAJOR GREATER 9)
	message("-- CUDA ${CUDA_VERSION_MAJOR} detected, enabling SM_72")

	set(
		CUDA_NVCC_FLAGS
		${CUDA_NVCC_FLAGS}; 
		-gencode arch=compute_72,code=sm_72
	)

endif()

# tensorRT
message("CUDA_TOOLKIT_ROOT_DIR = ${CUDA_TOOLKIT_ROOT_DIR}")

find_path(TENSORRT_INCLUDE_DIR NvInfer.h
  HINTS ${TENSORRT_ROOT} ${CUDA_TOOLKIT_ROOT_DIR} /usr/include
  PATH_SUFFIXES include)
find_path(TENSORRT_INCLUDE_DIR NvInferPlugin.h
  HINTS ${TENSORRT_ROOT} ${CUDA_TOOLKIT_ROOT_DIR}
  PATH_SUFFIXES include)
MESSAGE(STATUS "Found TensorRT headers at ${TENSORRT_INCLUDE_DIR}")
find_library(TENSORRT_LIBRARY_INFER nvinfer
  HINTS ${TENSORRT_ROOT} ${TENSORRT_BUILD} ${CUDA_TOOLKIT_ROOT_DIR}
  PATH_SUFFIXES lib lib64 lib/x64 lib/aarch64-linux-gnu)
find_library(TENSORRT_LIBRARY_INFER_PLUGIN nvinfer_plugin
  HINTS  ${TENSORRT_ROOT} ${TENSORRT_BUILD} ${CUDA_TOOLKIT_ROOT_DIR}
  PATH_SUFFIXES lib lib64 lib/x64 lib/aarch64-linux-gnu)
  find_library(TENSORRT_LIBRARY_PARSER nvparsers
  HINTS  ${TENSORRT_ROOT} ${TENSORRT_BUILD} ${CUDA_TOOLKIT_ROOT_DIR}
  PATH_SUFFIXES lib lib64 lib/x64 lib/aarch64-linux-gnu)
set(TENSORRT_LIBRARY ${TENSORRT_LIBRARY_INFER} ${TENSORRT_LIBRARY_INFER_PLUGIN} ${TENSORRT_LIBRARY_PARSER})
message(STATUS "Find TensorRT libs at ${TENSORRT_LIBRARY}")
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  TENSORRT DEFAULT_MSG TENSORRT_INCLUDE_DIR TENSORRT_LIBRARY)
if(NOT TENSORRT_FOUND)
  message(ERROR
    "Cannot find TensorRT library.")
endif()

# l2norm_helper plugin
add_subdirectory(trt_l2norm_helper)
include_directories(
  trt_l2norm_helper
  ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}
  ${TENSORRT_INCLUDE_DIR}
  ${X11_INCLUDE_DIR}
  "./src/"
)
message("CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES = $(CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES)")
message("TENSORRT_INCLUDE_DIR = ${TENSORRT_INCLUDE_DIR}")
message("TENSORRT_LIBRARY = ${TENSORRT_LIBRARY}")

AUX_SOURCE_DIRECTORY(./src DIR_SRCS)
message("DIR_SRCS = ${DIR_SRCS}")
cuda_add_executable(${PROJECT_NAME} ${DIR_SRCS} "./src/qml.qrc" "./src/request.h" "./src/presentation.h" "./src/loop.h")

target_link_libraries(${PROJECT_NAME}
  trt_l2norm_helper
  ${TENSORRT_LIBRARY}
)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${X11_LIBRARIES})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick Qt5::Widgets)
