class Teste2 {
    public static int x;

    public static int primeiro() {
        x = 1;
        return x;
    }

    public static int segundo() {
        x = 2;
        return x;
    }

    public static void somar(int a, int b) {
        System.out.print(a);
        System.out.print(b);
        System.out.print(x);
    }

    public static void main(String[] args) {
        x = 0;
        // primeiro() corre (x=1), depois segundo() corre (x=2).
        // A função somar deve imprimir a, b e o último valor de x (2)
        somar(primeiro(), segundo());
    }
}