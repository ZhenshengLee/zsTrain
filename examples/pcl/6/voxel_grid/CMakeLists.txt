find_package(PCL REQUIRED)
add_executable(voxel_grid voxel_grid.cpp)
add_definitions(${PCL_DEFINITIONS})
target_include_directories(voxel_grid PRIVATE ${PCL_INCLUDE_DIRS})
target_link_directories(voxel_grid PRIVATE ${PCL_LIBRARY_DIRS})
target_link_libraries(voxel_grid PRIVATE ${PCL_LIBRARIES})

