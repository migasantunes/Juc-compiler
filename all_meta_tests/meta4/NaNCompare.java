class NaNCompare {
    public static void main(String[] args) {
        double x;
        boolean b;
        x = 0.0 / 0.0;
        b = x != x;
        System.out.print(b);
        System.out.print("\n");
        b = x == x;
        System.out.print(b);
        System.out.print("\n");
    }
}
