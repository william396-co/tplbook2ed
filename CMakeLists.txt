cmake_minimum_required(VERSION 3.20)

project(tplbook2ed LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC AND NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(WARNING
        "This project is expected to build with the ClangCL toolset on Windows. "
        "Configure with: cmake -S . -B build-clang -T ClangCL"
    )
endif()

add_executable(tplbook2ed
    tplbook2ed/main.cpp
    PartI-TheBasics/Chapter1-FunctionTemplates.cpp
    PartI-TheBasics/Chapter10-BasicTemplateTerminology.cpp
    PartI-TheBasics/Chapter11-GenericLibraries.cpp
    PartI-TheBasics/Chapter2-ClassTemplates.cpp
    PartI-TheBasics/Chapter3-NontypeTemplateParameters.cpp
    PartI-TheBasics/Chapter4-VariadicTemplates.cpp
    PartI-TheBasics/Chapter5-TrickyBasics.cpp
    PartI-TheBasics/Chapter6-MoveSemantic_EnableIf.cpp
    PartI-TheBasics/Chapter7-ByValueByRef.cpp
    PartI-TheBasics/Chapter9-UsingTemplatesInPractice.cpp
    PartI-TheBasics/Chpater8-CompileTimeProgramming.cpp
    PartI-TheBasics/Chapter9-Impl.cpp
    PartII-TemplatesInDepth/Chapter12-FundamentalsInDepth.cpp
    PartIII-TemplatesAndDesign/Chapter18-ThePolymorphicPowerOfTemplates.cpp
    PartIII-TemplatesAndDesign/Chpater19-ImplementingTraits.cpp
    PartI-TheBasics/Chapter1-FunctionTemplates.h
    PartI-TheBasics/Chapter10-BasicTemplateTerminology.h
    PartI-TheBasics/Chapter11-GenericLibraries.h
    PartI-TheBasics/Chapter2-ClassTemplates.h
    PartI-TheBasics/Chapter3-NontypeTemplateParameters.h
    PartI-TheBasics/Chapter4-VariadicTemplates.h
    PartI-TheBasics/Chapter5-TrickyBasics.h
    PartI-TheBasics/Chapter6-MoveSemantic_EnableIf.h
    PartI-TheBasics/Chapter7-ByValueByRef.h
    PartI-TheBasics/Chapter9-UsingTemplatesInPractice.h
    PartI-TheBasics/Chpater8-CompileTimeProgramming.h
    PartII-TemplatesInDepth/Chapter12-FundamentalsInDepth.h
    PartIII-TemplatesAndDesign/Chapter18-ThePolymorphicPowerOfTemplates.h
    PartIII-TemplatesAndDesign/Chpater19-ImplementingTraits.h
)

target_compile_features(tplbook2ed PRIVATE cxx_std_20)

if(MSVC)
    target_compile_options(tplbook2ed PRIVATE /W3 /permissive-)
else()
    target_compile_options(tplbook2ed PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT tplbook2ed)
