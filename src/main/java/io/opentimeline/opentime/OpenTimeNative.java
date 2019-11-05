package io.opentimeline.opentime;

import java.io.IOException;
import io.opentimeline.NativeUtils;

public class OpenTimeNative {

    static {
        OpenTimeNative.loadNative();
    }

    private static boolean isLoaded = false;

    private static void loadNative() {
        if (isLoaded) {
            return;
        }

        final String libname = System.mapLibraryName("opentime-jni");
        final String libPkgPath = "/lib/" + libname;
        System.out.println("loading from: " + libPkgPath);
        try {
            /*
             * System.err.println(loader); final URL libraryURL =
             * RationalTime.class.getResource(libPkgPath); System.err.println(libraryURL);
             * final String libraryPath = libraryURL.getPath();
             * System.out.println(libraryPath); System.load(libraryPath);
             */
            NativeUtils.loadLibraryFromJar(libPkgPath);
            isLoaded = true;
        } catch (IllegalArgumentException | IOException e) {
            System.err.println("Could not find opentime native in jar, falling back to system path");
            System.loadLibrary("opentime-jni");
            isLoaded = true;
        } catch (Exception e) {
            System.err.println("Error loading native library:");
            System.err.println(e);
        }
    }
}