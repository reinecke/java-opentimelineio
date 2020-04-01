javasources := $(shell find src/main/java -name "*.java" -print)
destfiles := $(subst /native/,/,$(patsubst src/main/java/io/%.java,build/io/%.class,$(javasources)))

opentimenative := $(shell find src/main/java/io/opentimeline/opentime/native -name "*.java" -print)
opentimelineionative := $(shell find src/main/java/io/opentimeline/opentimelineio/native -name "*.java" -print)
native_sources := $(opentimenative) $(opentimelineionative)
gen_header_names := $(subst /,_,$(patsubst src/main/java/%.java,%.h,$(subst /native/,/,$(native_sources))))
gen_headers := $(patsubst %,build/include/%,$(gen_header_names))

cpp_sources := $(shell find src/main/jni/opentime src/main/jni/opentimelineio -name "*.cpp" -print)

java_home := $(shell dirname $(shell java -XshowSettings:properties -version 2>&1 > /dev/null | grep 'java.home' | cut -d "=" -f 2))


default: classes libraries jar
	#echo ${javasources}
	#echo ${opentimenative}
	#echo ${opentimelineionative}
	#echo ${java_home}
	echo "--------------"
	#echo ${destfiles}
	echo ${native_sources}
	echo ${native_gen_headers}

build/opentimelineio.jar: build classes libraries
	mkdir -p build/jar
	cp -r build/io build/jar
	cp -r build/lib build/jar
	cp -r opentimelineio/lib/* build/jar/lib/
	jar cvf build/opentimelineio.jar -C build/jar .

jar: build/opentimelineio.jar

build: build/lib build/include

build/lib:
	mkdir -p build/lib

build/include:
	mkdir -p build/include

# CPP
build/lib/libopentime-jni.dylib: nativeheaders
	clang++ -shared -std=c++11 -fPIC -I${java_home}/include -I${java_home}/include/darwin -Iopentimelineio/include -Iopentimelineio/include/opentimelineio/deps -Isrc/main/jni/include -Ibuild/include -Lopentimelineio/lib -lopentime -lopentimelineio -o $@ ${cpp_sources}

libraries: build/lib/libopentime-jni.dylib

# Java build
build/io/opentimeline/%.class: $(javasources)
	javac -sourcepath src/main/java -d build $(javasources)

build/include/%.h: $(native_sources)
	javac -sourcepath src/main/java -h build/include $(native_sources)

classes: build $(destfiles)

nativeheaders: $(gen_headers)

build/TestRT.class: jar
	javac -d build TestRT.java -cp build

runtest: build/TestRT.class
	java -cp build TestRT

.PHONY: classes default nativeheaders libraries jar runtest
