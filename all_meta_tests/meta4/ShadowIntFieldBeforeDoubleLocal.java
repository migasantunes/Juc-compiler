class ShadowTest {
    public static int x;
    public static void main(String[] args) {
        System.out.print(x);
        System.out.print("\n");
        x = 7 + x;
        System.out.print(x);
        System.out.print("\n");
        double x;
        x = 2.75;
        System.out.print(x > 2.5);
        System.out.print("\n");
    }
}
