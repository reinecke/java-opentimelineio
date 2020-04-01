import io.opentimeline.opentime.RationalTime;
import io.opentimeline.opentime.TimeRange;

public class TestRT {
    public static void main(String[] args) {
        System.out.println("----- Begin RationalTime smoketest");

        // Test adding two rationals
        RationalTime rt1 = new RationalTime(1, 24);
        RationalTime rt2 = new RationalTime(48, 24);
        RationalTime sum = rt1.add(rt2);

        System.out.println("The next line should be 49/24:");
        System.out.println(sum.getValue() + "/" + sum.getRate());

        // Test creating a time range
        TimeRange range = new TimeRange(
            new RationalTime(48, 24), new RationalTime(12, 24)
        );

        System.out.println("The next two lines should be 48->60:");
        System.out.println(range.getStartTime().getValue() + "->" + (range.getDuration().getValue() + range.getStartTime().getValue()));
        System.out.println(range.getStartTime().getValue() + "->" + range.endTimeExclusive().getValue());

        System.out.println("----- End RationalTime smoketest");
    }
}
