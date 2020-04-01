#include <opentime/version.h>
#include <opentime/rationalTime.h>
#include <opentime/timeRange.h>

#include "handle.h"
#include "utilities.h"

#include "io_opentimeline_opentime_TimeRange.h"

using namespace std;

namespace otio = opentime::OPENTIME_VERSION;

/*
 * Class:     io_opentimeline_opentime_TimeRange
 * Method:    initialize
 * Signature: (Lio/opentimeline/opentime/RationalTime;Lio/opentimeline/opentime/RationalTime;)V
 */
JNIEXPORT void JNICALL Java_io_opentimeline_opentime_TimeRange_initialize(JNIEnv *env, jobject thisObj, jobject start_time, jobject duration)
{
    auto c_start_time = getHandle<otio::RationalTime>(env, start_time);
    auto c_duration = getHandle<otio::RationalTime>(env, duration);

    otio::TimeRange *tr = new otio::TimeRange(*c_start_time, *c_duration);
    setHandle(env, thisObj, tr);
}

/*
 * Class:     io_opentimeline_opentime_TimeRange
 * Method:    getStartTime
 * Signature: ()Lio/opentimeline/opentime/RationalTime;
 */
JNIEXPORT jobject JNICALL Java_io_opentimeline_opentime_TimeRange_getStartTime(JNIEnv *env, jobject thisObj)
{
    auto this_ = getHandle<otio::TimeRange>(env, thisObj);
    otio::RationalTime *c_start_time = new otio::RationalTime(this_->start_time().value(), this_->start_time().rate());
    jobject start_time = rationalTimeFromNative(env, c_start_time);

    return start_time;
}

/*
 * Class:     io_opentimeline_opentime_TimeRange
 * Method:    getDuration
 * Signature: ()Lio/opentimeline/opentime/RationalTime;
 */
JNIEXPORT jobject JNICALL Java_io_opentimeline_opentime_TimeRange_getDuration(JNIEnv *env, jobject thisObj)
{
    auto this_ = getHandle<otio::TimeRange>(env, thisObj);
    otio::RationalTime *c_duration = new otio::RationalTime(this_->duration().value(), this_->duration().rate());
    jobject duration = rationalTimeFromNative(env, c_duration);

    return duration;

    /*
    auto this_ = getHandle<otio::TimeRange>(env, thisObj);
    otio::RationalTime c_duration = this_->duration();
    otio::RationalTime *durationptr = &c_duration;
    jobject duration = rationalTimeFromNative(env, durationptr);

    return duration;
    */
}

/*
 * Class:     io_opentimeline_opentime_TimeRange
 * Method:    endTimeExclusive
 * Signature: ()Lio/opentimeline/opentime/RationalTime;
 */
JNIEXPORT jobject JNICALL Java_io_opentimeline_opentime_TimeRange_endTimeExclusive(JNIEnv *env, jobject thisObj)
{
    auto this_ = getHandle<otio::TimeRange>(env, thisObj);
    auto c_end_time = this_->end_time_exclusive();
    auto c_end_time_ptr = new otio::RationalTime(c_end_time.value(), c_end_time.rate());
    jobject end_time = rationalTimeFromNative(env, c_end_time_ptr);

    return end_time;
}
