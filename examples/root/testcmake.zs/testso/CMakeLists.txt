# aux_source_directory(. sourceList)
# message(${sourceList})

add_executable(maintestso ./maintestso.cc)

include_directories(./include)

target_link_libraries(maintestso
calculate
sub
mul
add
)