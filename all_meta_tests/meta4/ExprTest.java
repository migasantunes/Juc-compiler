class ExprTest {
    public static void main(String[] args) {
        int a, b;
        double d;
        boolean bl;
        
        // XOR operations
        a = 5 ^ 3;
        System.out.print(a);
        System.out.print("\n");
        
        // LSHIFT
        a = 1 << 4;
        System.out.print(a);
        System.out.print("\n");
        
        // RSHIFT
        a = 32 >> 2;
        System.out.print(a);
        System.out.print("\n");
        
        // MOD
        a = 17 % 5;
        System.out.print(a);
        System.out.print("\n");
        
        // Relational with doubles
        d = 1.5;
        bl = d > 1.0;
        System.out.print(bl);
        System.out.print("\n");
        
        bl = d < 2.0;
        System.out.print(bl);
        System.out.print("\n");
        
        bl = d == 1.5;
        System.out.print(bl);
        System.out.print("\n");
        
        bl = d != 1.0;
        System.out.print(bl);
        System.out.print("\n");
        
        // Boolean XOR
        bl = true ^ false;
        System.out.print(bl);
        System.out.print("\n");
        
        bl = true ^ true;
        System.out.print(bl);
        System.out.print("\n");
        
        // Nested expressions
        a = (3 + 4) * 2 - 1;
        System.out.print(a);
        System.out.print("\n");
        
        // Unary minus double
        d = -1.5;
        System.out.print(d);
        System.out.print("\n");
        
        // Unary plus
        a = +5;
        System.out.print(a);
        System.out.print("\n");
        
        // Integer division
        a = 7 / 2;
        System.out.print(a);
        System.out.print("\n");
        
        // Double division
        d = 7.0 / 2.0;
        System.out.print(d);
        System.out.print("\n");
        
        // Mixed int/double
        d = 7 / 2.0;
        System.out.print(d);
        System.out.print("\n");
        
        // Comparison result used in expression
        a = 5;
        b = 3;
        bl = (a > b) && (b > 0);
        System.out.print(bl);
        System.out.print("\n");
        
        bl = (a < b) || (b > 0);
        System.out.print(bl);
        System.out.print("\n");
        
        // NOT
        bl = !true;
        System.out.print(bl);
        System.out.print("\n");
        
        bl = !false;
        System.out.print(bl);
        System.out.print("\n");
        
        // Complex: int promoted in comparison
        bl = 5 > 3.0;
        System.out.print(bl);
        System.out.print("\n");
    }
}
