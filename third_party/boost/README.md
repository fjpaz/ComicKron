Boost
=====

Subset of Boost 1.57. Boost provides free peer-reviewed portable C++ source libraries. Upstream version [here](https://github.com/boostorg).

Modifications are intended to integrate Boost in ComicKron build only with needed files and add Boost.DI.

Changelog:
* Remove non-needed libraries
* Remove upstream build files
* Add Boost.DI library
* Integrate Boost in ComicKron build (qmake)

Boost is licensed under the terms of [Boost Software License, Version 1.0](http://www.boost.org/LICENSE_1_0.txt).

Boost.DI is a C++03/11 header only library providing type safe, compile time, macro free constructor dependency injection. Upstream version [here](https://github.com/krzysztof-jusiak/di/tree/cpp03).

Changelog:
* Remove everything except source code folder
* Add object scope and uniqueref wrapper

Boost.DI is licensed under the terms of [Boost Software License, Version 1.0](http://www.boost.org/LICENSE_1_0.txt).
