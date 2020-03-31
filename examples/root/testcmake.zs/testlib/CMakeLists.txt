# aux_source_directory(. sourceList)
# message(${sourceList})

add_executable(maintestlib ./maintestlib.cc)

include_directories(./include)

target_link_libraries(maintestlib
calculate_static
)