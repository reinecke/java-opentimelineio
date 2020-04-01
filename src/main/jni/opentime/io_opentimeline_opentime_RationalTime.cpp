#include <iostream>

#include <opentime/version.h>
#include <opentime/rationalTime.h>
#include <opentimelineio/deserialization.h>
#include <opentimelineio/timeline.h>
#include <opentimelineio/errorStatus.h>

#include "handle.h"
#include "utilities.h"
#include "io_opentimeline_opentime_RationalTime.h"

using namespace std;

namespace otio = opentime::OPENTIME_VERSION;
namespace otio2 = opentimelineio::OPENTIMELINEIO_VERSION;


/*
 * Class:     io_opentimeline_RationalTime
 * Method:    initialize
 * Signature: (DD)V
 */
JNIEXPORT void JNICALL Java_io_opentimeline_opentime_RationalTime_initialize(JNIEnv *env, jobject thisObj, jdouble value, jdouble rate)
{
    otio::RationalTime *rt = new otio::RationalTime(value, rate);
    setHandle(env, thisObj, rt);
}

/*
 * Class:     io_opentimeline_RationalTime
 * Method:    getValue
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_io_opentimeline_opentime_RationalTime_getValue(JNIEnv *env, jobject thisObj)
{
  auto this_ = getHandle<otio::RationalTime>(env, thisObj);
  return this_->value();
}

/*
 * Class:     io_opentimeline_RationalTime
 * Method:    getRate
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_io_opentimeline_opentime_RationalTime_getRate(JNIEnv *env, jobject thisObj)
{
    auto this_ = getHandle<otio::RationalTime>(env, thisObj);
    return this_->rate();
}

/*
 * Class:     io_opentimeline_RationalTime
 * Method:    add
 * Signature: (Lio/opentimeline/RationalTime;)Lio/opentimeline/RationalTime;
 */
JNIEXPORT jobject JNICALL
Java_io_opentimeline_opentime_RationalTime_add(JNIEnv *env, jobject thisObj, jobject other) {
    auto this_ = getHandle<otio::RationalTime>(env, thisObj);
    auto other_ = getHandle<otio::RationalTime>(env, other);
    auto result = (*this_ + *other_);

    return rationalTimeFromNative(env, new otio::RationalTime(result));
}


/*
 * Class:     io_opentimeline_opentime_RationalTime
 * Method:    subtract
 * Signature: (Lio/opentimeline/opentime/RationalTime;)Lio/opentimeline/opentime/RationalTime;
 */
JNIEXPORT jobject JNICALL
Java_io_opentimeline_opentime_RationalTime_subtract (JNIEnv *env, jobject thisObj, jobject other) {
    auto this_ = getHandle<otio::RationalTime>(env, thisObj);
    auto other_ = getHandle<otio::RationalTime>(env, other);
    auto result = (*this_ - *other_);

    return rationalTimeFromNative(env, new otio::RationalTime(result));
}


/*
 * Class:     io_opentimeline_opentime_RationalTime
 * Method:    compareTo
 * Signature: (Lio/opentimeline/opentime/RationalTime;)I
 */
JNIEXPORT jint JNICALL
Java_io_opentimeline_opentime_RationalTime_compareTo(JNIEnv *env, jobject thisObj, jobject other) {
    auto this_ = *getHandle<otio::RationalTime>(env, thisObj);
    auto other_ = *getHandle<otio::RationalTime>(env, other);

    if (this_ < other_) {
        return -1;
    }
    else if (this_ > other_) {
        return 1;
    }
    else if (this_ == other_) {
        return 0;
    }

    // This should be impossible
    return -99;
}

/*
 * Class:     io_opentimeline_opentime_RationalTime
 * Method:    getCrazy
 * Signature: ()V
 */
JNIEXPORT void JNICALL
Java_io_opentimeline_opentime_RationalTime_getCrazy(JNIEnv *, jobject) {
    otio2::ErrorStatus error = otio2::ErrorStatus();
    auto tl = new otio2::Timeline();
    auto tlAny = otio2::any(tl);
    bool success = otio2::deserialize_json_from_file("/Users/ereinecke/Downloads/test.otio", &tlAny, &error);
    if (!success) {
        cout << "Error reading timeline: " << error.full_description << endl;
        return;
    }
    cout << "Timeline name: " << tl->name() << endl;
}
