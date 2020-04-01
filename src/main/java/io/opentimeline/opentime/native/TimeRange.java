package io.opentimeline.opentime;

public class TimeRange extends OpenTimeNative {
   public long nativeHandle;

   public TimeRange() {
      this.initialize(new RationalTime(), new RationalTime());
   }

   public TimeRange(RationalTime start_time, RationalTime Duration) {
      this.initialize(start_time, Duration);
   }

   public TimeRange(long nativeHandle) {
      this.nativeHandle = nativeHandle;
   }

   private native void initialize(RationalTime start_time, RationalTime duration);

   public native RationalTime getStartTime();

   public native RationalTime getDuration();

   public native RationalTime endTimeExclusive();

}
