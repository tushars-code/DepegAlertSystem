cmake_minimum_required(VERSION 3.15)


if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT
      "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()


set(CMAKE_TOOLCHAIN_FILE "C:/Users/Tushar/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")

set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "")

project(DepegAlertSystem)


include_directories(${Boost_INCLUDE_DIRS})



add_subdirectory(DepegAlertSystem)
