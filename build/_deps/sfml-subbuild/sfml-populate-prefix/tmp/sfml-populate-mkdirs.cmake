# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "H:/Logan/Programming_Projects/C++_Projects/github-repos/RandomKingOnChessboard/build/_deps/sfml-src"
  "H:/Logan/Programming_Projects/C++_Projects/github-repos/RandomKingOnChessboard/build/_deps/sfml-build"
  "H:/Logan/Programming_Projects/C++_Projects/github-repos/RandomKingOnChessboard/build/_deps/sfml-subbuild/sfml-populate-prefix"
  "H:/Logan/Programming_Projects/C++_Projects/github-repos/RandomKingOnChessboard/build/_deps/sfml-subbuild/sfml-populate-prefix/tmp"
  "H:/Logan/Programming_Projects/C++_Projects/github-repos/RandomKingOnChessboard/build/_deps/sfml-subbuild/sfml-populate-prefix/src/sfml-populate-stamp"
  "H:/Logan/Programming_Projects/C++_Projects/github-repos/RandomKingOnChessboard/build/_deps/sfml-subbuild/sfml-populate-prefix/src"
  "H:/Logan/Programming_Projects/C++_Projects/github-repos/RandomKingOnChessboard/build/_deps/sfml-subbuild/sfml-populate-prefix/src/sfml-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "H:/Logan/Programming_Projects/C++_Projects/github-repos/RandomKingOnChessboard/build/_deps/sfml-subbuild/sfml-populate-prefix/src/sfml-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "H:/Logan/Programming_Projects/C++_Projects/github-repos/RandomKingOnChessboard/build/_deps/sfml-subbuild/sfml-populate-prefix/src/sfml-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
