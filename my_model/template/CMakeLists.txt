################################################################################
# These stub libraries allow us to test the basic interface. They are linked
# against the test drivers defined in ../driver.

add_library(my_model_fortran_stub
            fortran/my_model.F90
            fortran/model_factory.F90)

add_library(my_model_cpp_stub
            cpp/my_model.cpp
            cpp/model_factory.F90)

add_library(my_model_c_stub
            c/my_model.c
            c/model_factory.F90)

foreach (language fortran cpp c)
  target_link_libraries(my_model_${language}_stub PUBLIC aero)
  target_include_directories(my_model_${language}_stub PUBLIC
                             ${CMAKE_SOURCE_DIR}/include)
endforeach()

################################################################################
