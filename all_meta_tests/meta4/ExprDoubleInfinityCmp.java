class ExprDoubleInfinityCmp {
    public static void main(String[] args) {
        double p;
        double q;
        p = 1.0;
        q = 0.0;
        System.out.print(p / q > 1e10);
        System.out.print("\n");
        System.out.print(p / q == p / q);
        System.out.print("\n");
    }
}
