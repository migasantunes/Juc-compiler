class Teste4 {
    public static boolean flag;

    public static boolean mudaEstado() {
        flag = true;
        return true;
    }

    public static void check(boolean a) {
        System.out.print(0);
    }

    public static void check(int a) {
        System.out.print(1);
    }

    public static void main(String[] args) {
        flag = false;
        boolean temp;
        
        // false AND ... -> short-circuit! mudaEstado() NÃO PODE CORRER
        temp = false && mudaEstado();
        System.out.print(flag); // Tem de imprimir false
        
        // true OR ... -> short-circuit! mudaEstado() NÃO PODE CORRER
        temp = true || mudaEstado();
        System.out.print(flag); // Tem de imprimir false

        // false OR ... -> mudaEstado() CORRE! flag passa a true
        temp = false || mudaEstado();
        System.out.print(flag); // Tem de imprimir true
        
        // Testa a sobrecarga baseada na invocação (chama check(int))
        check(5);
    }
}