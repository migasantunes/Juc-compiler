class ExprBoolEqChain {
    public static void main(String[] args) {
        boolean a;
        boolean b;
        boolean c;
        a = true;
        b = false;
        c = true;
        System.out.print(a == b == false);
        System.out.print("\n");
        System.out.print(a == b == b);
        System.out.print("\n");
        System.out.print(c == c == true);
        System.out.print("\n");
    }
}
