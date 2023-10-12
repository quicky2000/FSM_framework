cmake_minimum_required(VERSION 3.8)
project(FSM_framework)

set(CMAKE_CXX_STANDARD 11)

set(MY_SOURCE_FILES
    include/algorithm_basic.h
    include/algorithm_deep.h
    include/algorithm_deep_first.h
    include/algorithm_deep_first_weighted.h
    include/algorithm_deep_raw.h
    include/algorithm_wide.h
    include/algorithm_wide_first.h
    include/framework_algorithm_if.h
    include/framework_algorithm_UI_if.h
    include/framework_base.h
    include/framework_controler.h
    include/framework_UI_if.h
    include/FSM_weighted_transition_index_comparator.h
    include/investigated_situation.h
    include/pointer_comparator.h
    include/situation_manager.h
    include/situation_stack.h
    include/situation_tree_node.h
    include/smart_situation_stack.h
    src/algorithm_basic.cpp
    src/algorithm_deep.cpp
    src/algorithm_deep_first.cpp
    src/algorithm_deep_first_weighted.cpp
    src/algorithm_deep_raw.cpp
    src/algorithm_wide.cpp
    src/algorithm_wide_first.cpp
    src/framework_algorithm_if.cpp
    src/framework_base.cpp
    src/framework_controler.cpp
    src/framework_UI_if.cpp
    src/FSM_weighted_transition_index_comparator.cpp
    src/situation_manager.cpp
    src/situation_tree_node.cpp)

# List header directories in project
set(MY_INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

#Create dependancy list
set(DEPENDANCY_LIST "")
LIST(APPEND DEPENDANCY_LIST "FSM_interfaces")
LIST(APPEND DEPENDANCY_LIST "quicky_exception")

#------------------------------
#- Generic part
#------------------------------
set(DEPENDANCY_OBJECTS "")
set(LINKED_LIBRARIES "-ldl")
#iterate on dependancies
foreach(DEPENDANCY_ITEM IN ITEMS ${DEPENDANCY_LIST})
    message("${PROJECT_NAME} need dependancy ${DEPENDANCY_ITEM}")
    set(IS_IMPORTED FALSE)
    #Get information from dependancies if not already done
    if(NOT TARGET ${DEPENDANCY_ITEM})
        set(SUB_DEPENDANCY_OBJECTS "")
        set(SUB_LINKED_LIBRARIES "")
        message("${PROJECT_NAME} include dependancy ${DEPENDANCY_ITEM}")
        add_subdirectory($ENV{QUICKY_REPOSITORY}/${DEPENDANCY_ITEM} ${CMAKE_CURRENT_BINARY_DIR}/${DEPENDANCY_ITEM})
        get_target_property(IS_IMPORTED ${DEPENDANCY_ITEM} IMPORTED)
        if(NOT ${IS_IMPORTED})
            list(APPEND DEPENDANCY_OBJECTS "$<TARGET_OBJECTS:${DEPENDANCY_ITEM}>" ${SUB_DEPENDANCY_OBJECTS})
        else()
            list(APPEND LINKED_LIBRARIES ${DEPENDANCY_ITEM})
        endif()
        list(APPEND LINKED_LIBRARIES ${SUB_LINKED_LIBRARIES})
    endif()

    # Complete include directories with directories coming from dependancy because of transitivity issues with Object libraries
    if(NOT ${IS_IMPORTED})
        set(MY_INCLUDE_DIRECTORIES ${MY_INCLUDE_DIRECTORIES} $<TARGET_PROPERTY:${DEPENDANCY_ITEM},INCLUDE_DIRECTORIES>)
    endif()
endforeach(DEPENDANCY_ITEM)


#Prepare targets
get_directory_property(HAS_PARENT PARENT_DIRECTORY)
if(IS_DIRECTORY ${HAS_PARENT})
    message("Declare library ${PROJECT_NAME}")
    add_library(${PROJECT_NAME} OBJECT ${MY_SOURCE_FILES})
    set(SUB_DEPENDANCY_OBJECTS ${DEPENDANCY_OBJECTS} PARENT_SCOPE)
    set(SUB_LINKED_LIBRARIES ${LINKED_LIBRARIES} PARENT_SCOPE)
else()
    #set(CMAKE_VERBOSE_MAKEFILE ON)
    add_executable(${PROJECT_NAME} ${MY_SOURCE_FILES} ${DEPENDANCY_OBJECTS} src/main_${PROJECT_NAME}.cpp)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -D$<UPPER_CASE:${PROJECT_NAME}>_SELF_TEST)
    target_link_libraries(${PROJECT_NAME} ${LINKED_LIBRARIES})
    target_compile_options(${PROJECT_NAME} PUBLIC -Wall -pedantic -g -O0)
    target_link_libraries(${PROJECT_NAME})
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${MY_INCLUDE_DIRECTORIES})

foreach(DEPENDANCY_ITEM IN ITEMS ${DEPENDANCY_LIST})
    add_dependencies(${PROJECT_NAME} ${DEPENDANCY_ITEM})
endforeach(DEPENDANCY_ITEM)

#Force use of -std=c++11 instead of -std=gnu++11
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

#EOF
