cmake_minimum_required(VERSION 3.10)
project(trt LANGUAGES CXX CUDA)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/workspace)
set(CMAKE_CUDA_ARCHITECTURES 89)

set(CUDA_TOOLKIT_ROOT_DIR /usr/local/cuda-11.8)
set(OPENCV_DIR /home/user/thirdparty/opencv4.8.1)
set(TRT_DIR /home/user/thirdparty/TensorRT-8.6.1.6)
set(CUDNN_DIR /home/user/thirdparty/cudnn-linux-x86_64-8.9.7.29_cuda11-archive)
# set(python_include_path /home/user/miniconda3/envs/yolo/include/python3.10)


include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${CUDA_TOOLKIT_ROOT_DIR}/include
    ${OPENCV_DIR}/include/opencv4
    ${TRT_DIR}/include
    ${CUDNN_DIR}/include
    ${python_include_path}
)

link_directories(
    ${CUDA_TOOLKIT_ROOT_DIR}/lib64
    ${OPENCV_DIR}/lib
    ${TRT_DIR}/lib
    ${CUDNN_DIR}/lib
)


set(CMAKE_CXX_FLAGS "-std=c++17 -w -g -O0 -m64 -fPIC -fopenmp -pthread")

set(CUDA_NVCC_FLAGS "-std=c++17 -w -g -O0 -m64 -fPIC -fopenmp -pthread -Xcompiler")
set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS}  -gencode=arch=compute_89,code=compute_89)


file(GLOB_RECURSE cpp_srcs ${PROJECT_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM cpp_srcs ${PROJECT_SOURCE_DIR}/src/common/tensorrt.cpp ${PROJECT_SOURCE_DIR}/src/interface.cpp)



file(GLOB_RECURSE cuda_srcs ${PROJECT_SOURCE_DIR}/src/*.cu)
# set_source_files_properties(${cuda_srcs} PROPERTIES LANGUAGE CUDA)

add_executable(pro ${cpp_srcs} ${cuda_srcs})
target_link_libraries(pro nvinfer nvinfer_plugin nvonnxparser)
target_link_libraries(pro cuda cublas cudart cudnn)
target_link_libraries(pro opencv_core opencv_imgproc opencv_videoio opencv_imgcodecs)
target_link_libraries(pro stdc++ dl)
set_target_properties(pro PROPERTIES LINK_FLAGS "-Wl,-rpath,${CUDA_TOOLKIT_ROOT_DIR}/lib64:${CUDNN_DIR}/lib")



add_custom_target(
    run
    DEPENDS pro
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/workspace
    COMMAND ./pro 
)