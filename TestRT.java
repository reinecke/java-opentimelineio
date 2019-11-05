import io.opentimeline.opentime.RationalTime;

public class TestRT {
    public static void main(String[] args) {
        RationalTime rt1 = new RationalTime(1, 24);
        RationalTime rt2 = new RationalTime(48, 24);
        RationalTime sum = rt1.add(rt2);
        System.out.println(sum.getValue() + "/" + sum.getRate());
    }
}