package io.opentimeline.opentime;

public class RationalTime extends OpenTimeNative implements Comparable<RationalTime> {
   public long nativeHandle;

   public RationalTime() {
      this.initialize(0d, 1d);
   }

   public RationalTime(double value, double rate) {
      this.initialize(value, rate);
   }

   public RationalTime(long nativeHandle) {
      this.nativeHandle = nativeHandle;
   }

   private native void initialize(double value, double rate);

   public native double getValue();

   public native double getRate();

   public native RationalTime add(RationalTime other);

   public native RationalTime subtract(RationalTime other);

   public native void getCrazy();

   @Override
   public native int compareTo(RationalTime other);

}