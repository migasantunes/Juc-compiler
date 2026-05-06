class ExprIntOverflowWrap {
    public static void main(String[] args) {
        int x;
        x = 2147483647;
        System.out.print(x + 1);
        System.out.print("\n");
        System.out.print(x + x + 2);
        System.out.print("\n");
    }
}
