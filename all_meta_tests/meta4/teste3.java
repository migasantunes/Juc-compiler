class Teste3 {
    public static double geraDouble(int a) {
        // O Java converte este int implicitamente para double ao retornar
        return a; 
    }

    public static void imprimeDouble(double d) {
        System.out.print(d);
    }

    public static void main(String[] args) {
        imprimeDouble(geraDouble(5));
    }
}