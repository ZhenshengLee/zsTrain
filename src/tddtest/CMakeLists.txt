add_library(zst_tddtest STATIC
            tddtest.cpp
            )

# Consumers should #include <zstinternal/tddtest.h>
target_include_directories(zst_tddtest PUBLIC
    ${ZST_PRIV_INCLUDE_DIR})

# Dependencies of this library
# target_link_libraries(zst_tddtest PUBLIC
#     azure::aziotsharedutil
#     zstinternal::logging)

# Define alias for other targets to link against
add_library(zstinternal::tddtest ALIAS zst_tddtest)