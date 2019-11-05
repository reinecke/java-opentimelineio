# Java OpenTimelineIO
This is a POC for building Java bindings for the OpenTimelineIO C++ API. 


## Instructions

# Pt. 1 OpenTimelineIO
- Clone the OpenTimelineIO repo and fetch submodules according to instructions
- export OTIO_ROOT=$(pwd)
- Build opentimelineio by doing the following from the git root:
- mkdir build && cd build
- on the next step, make sure you update the prefix with the path to your java-opentimelineio
- cmake -DCMAKE_INSTALL_PREFIX:PATH=/path/to/java-opentimelineio/opentimelineio ..
- make install

# Pt. 2 Java OTIO
- cd into the root of the java-opentimelineio repo

- export JAVA_HOME=$(dirname $(java -XshowSettings:properties -version 2>&1 > /dev/null | grep 'java.home' | cut -d "=" -f 2))
- pushd src/main/java
- javac -h . io/opentimeline/opentime/RationalTime.java 
- popd
- mkdir -p build/lib
- clang++ -shared -std=c++11 -fPIC -I"${JAVA_HOME}/include" -I"${JAVA_HOME}/include/darwin" -Iopentimelineio/include -I opentimelineio/include/opentimelineio/deps -Isrc/main/java -Lopentimelineio/lib -lopentime -lopentimelineio -o build/lib/libopentime-jni.dylib src/main/jni/io_opentimeline_opentime_RationalTime.cpp

- pushd src/main/java
- javac -d ../../../build io/opentimeline/NativeUtils.java io/opentimeline/opentime/RationalTime.java
- popd
- jar cvf opentime.jar -C build .
- javac -classpath opentime.jar TestRT.java
- java -classpath opentime.jar:. TestRT


# Packaging tips
- NativeUtils.loadLibraryFromJar("/natives/"+System.mapLibraryName("crypt"))
- https://github.com/adamheinrich/native-utils




### deprecated notes
- clang++ -shared -std=c++11 -fPIC -I"${JAVA_HOME}/include" -I"${JAVA_HOME}/include/darwin" -I/Users/ereinecke/envs/otio_cpp/include -I/Users/ereinecke/envs/otio_cpp/include/opentimelineio/deps -L/Users/ereinecke/envs/otio_cpp/lib -lopentime -lopentimelineio -o build/lib/libopentime-jni.dylib io_opentimeline_opentime_RationalTime.cpp 
