# Java OpenTimelineIO
This is a POC for building Java bindings for the OpenTimelineIO C++ API.

The main goal of this was to experiment with embedding the compliled libraries
in built jar files and building JNI bindings. There are many other issues to
address such as how memory management should work.

## Instructions

This was built on macOS Mojave with the Xcode developer tools (clang compiler).
Your mileage will likely vary a lot in other circumstances.

### Pt. 1 OpenTimelineIO
- Clone the OpenTimelineIO repo and fetch submodules according to instructions
- Build opentimelineio by doing the following from the repo root:
- `mkdir build && cd build`
- on the next step, make sure you update the prefix with the path to your where you cloned this repo. For instance, if you cloned java-opentimelineio to `~/Projects`, your prefix path would be `~/Projects/java-opentimelineio/opentimelineio`
- `cmake -DCMAKE_INSTALL_PREFIX:PATH=/path/to/java-opentimelineio/opentimelineio ..`
- `make install`
- You should now have an `opentimelineio` directory in your `java-opentimelineio` root

### Pt. 2 Java OTIO
- cd into the root of the java-opentimelineio repo
- `make runtest`
- You should see lots of building happen followed by the smoketest (`TestRT.java`) output.
- `OpenTimelineIO.jar` should now exist in the `build` dir.

## Known Issues/Open Questions

- [ ] Come up with memory management strategy.
- [ ] Come up with strategy for marshalling otio objects with less boilerplate/copying.
- [ ] Validate the compiled libray linking works when moving jar between systems.
- [ ] Look into if there is a way we can better consume the output of the OpenTimelineIO cmake build rather than building to our repo,
- [ ] Determine how to distribute pre-built jars for multiple platforms.
- [ ] Clarify any licensing issues surrounding `handle.h` (if we stick with that approach)

# Acknowledgments/References
- [Native Utils](https://github.com/adamheinrich/native-utils)
- [The Breakfast Post: Wrapping A C++ library with JNI](https://thebreakfastpost.com/2012/01/21/wrapping-a-c-library-with-jni-introduction/)
