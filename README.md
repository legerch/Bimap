Library containing an implementation for a _bidirectionnal map_ using C++ 11 standard

**Table of contents :**
- [1. Requirements](#1-requirements)
  - [1.1. C++ Standards](#11-c-standards)
  - [1.2. Dependencies](#12-dependencies)
- [2. How to build](#2-how-to-build)
  - [2.1. As a library](#21-as-a-library)
  - [2.2. As an header-only](#22-as-an-header-only)
- [3. How to use](#3-how-to-use)
- [4. Library details](#4-library-details)
  - [4.1. Implementation](#41-implementation)
  - [4.2. Tricks and tips](#42-tricks-and-tips)
  - [4.3. Alternatives](#43-alternatives)
- [5. Documentation](#5-documentation)
- [6. License](#6-license)

# 1. Requirements
## 1.1. C++ Standards

This library required at least **C++ 11** standard

## 1.2. Dependencies

Below, list of required dependencies:

| Dependencies | VCPKG package | Comments |
|:-:|:-:|:-:|
| [Google Tests][gtest-repo] | `gtest` | Only needed to run unit-tests |

> Dependency manager [VCPKG][vcpkg-tutorial] is not mandatory, this is only a note to be able to list needed packages

# 2. How to build
## 2.1. As a library

This library can be use as an _embedded library_ in a subdirectory of your project (like a _git submodule_ for example) :
1. In the **root** CMakeLists, add instructions:
```cmake
add_subdirectory(Bimap) # Or if library is put in a folder "dependencies" : add_subdirectory(dependencies/Bimap)
```

2. In the **application/library** CMakeLists, add instructions:
```cmake
# Link needed libraries
target_link_libraries(${PROJECT_NAME} PRIVATE bimap)
```

## 2.2. As an header-only

This library can also be used as a single _header-only_ library by directly use file: `lib/bimap.h`

# 3. How to use

Class `cmap::Bimap<KeyType, ValueType>` implements an interface similar to `std::map` where you can make a reverse lookup. Every key has only one value and every value corresponds to exactly one key.  
Usage example:
```cpp
#include "bimap.h"

#include <iostream>

void printBimap(const std::string &comment, const cmap::Bimap<int, std::string> &bimap)
{
    std::cout << comment << ": ";
    for(auto it = bimap.cbegin(); it != bimap.cend(); ++it){
        std::cout << "[" << it->first << "] = " << it->second << "; ";
    }
    std::cout << std::endl;
}

int main()
{
    /* Create a map of three (int, string) pairs */
    cmap::Bimap<int, std::string> mapNbsToStrs =
    {
        {1, "ONE"},
        {2, "TWO"},
        {3, "THREE"}
    };
    printBimap("1) Initial map", mapNbsToStrs);

    /* Search items */
    std::cout << "2a) Search by key [2]: " << mapNbsToStrs.getValue(2) << std::endl;
    std::cout << "2b) Search by value [\"TWO\"]: " << mapNbsToStrs.getKey("TWO") << std::endl;
    
    /* Add item */
    mapNbsToStrs.insert(4, "FOUR");
    printBimap("3) Add item", mapNbsToStrs);
    
    /* Remove item */
    mapNbsToStrs.erase(3);
    printBimap("4) Remove item", mapNbsToStrs);
 
    /* Clear map */
    mapNbsToStrs.clear();
    std::cout << std::boolalpha << "5) Map is empty: " << mapNbsToStrs.empty() << std::endl;

    return 0;
}
```

Will output:
```shell
1) Initial map: [1] = ONE; [2] = TWO; [3] = THREE; 
2a) Search by key [2]: TWO
2b) Search by value ["TWO"]: 2
3) Add item: [1] = ONE; [2] = TWO; [3] = THREE; [4] = FOUR; 
4) Remove item: [1] = ONE; [2] = TWO; [4] = FOUR; 
5) Map is empty: true
```

# 4. Library details
## 4.1. Implementation

Implementation of this _bimap_ is pretty simple: we use two [`std::map`][std-map-doc]. For each entries added to `<key, value>` map, we also insert item in the second map `<value, key>`.  
This allow to reduce complexity when searching by _keys_, complexity decrease from `O(n)` to `O(log(n))`.  
This comes with a cost: **memory usage is doubled**, so use this class _only_ when you really need it.

## 4.2. Tricks and tips

If you need to reduce search complexity and don't need an _ordered map_, you can use [`std::unordered_map`][std-unordered-map-doc] instead (which will decrease search complexity to `O(1)`).  
Simply replace those _aliases definitions_ inside `Bimap` class:
```cpp
using _ContainerKey = std::map<TypeKey, TypeValue>;
using _ContainerValue = std::map<TypeValue, TypeKey>;
```

## 4.3. Alternatives

If your project already have a dependency to [Boost libraries][boost-home], it will be beter to use class [Boost.Bimap][boost-bimap] instead of this class.

# 5. Documentation

All methods has been documented with [Doxygen][doxygen-official] utility, documentation can be generated by using:
```shell
# Run documentation generation
doxygen ./Doxyfile

# Under Windows OS, maybe doxygen is not added to the $PATH
"C:\Program Files\doxygen\bin\doxygen.exe" ./Doxyfile
```
> **Note:** You can also load the _Doxyfile_ into _Doxywizard_ (Doxygen GUI) and run generation.

# 6. License

This library is licensed under [MIT license][repo-license].

<!-- Links of this repository -->
[repo-license]: LICENSE

<!-- External links -->
[boost-home]: https://www.boost.org/
[boost-bimap]: https://www.boost.org/doc/libs/1_85_0/libs/bimap/doc/html/index.html
[doxygen-official]: https://www.doxygen.nl/index.html
[gtest-repo]: https://github.com/google/googletest
[std-map-doc]: https://en.cppreference.com/w/cpp/container/map
[std-unordered-map-doc]: https://en.cppreference.com/w/cpp/container/unordered_map

[vcpkg-tutorial]: https://github.com/legerch/develop-memo/tree/master/Toolchains/Build%20systems/VCPKG