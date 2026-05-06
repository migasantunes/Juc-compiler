class MainOverload {

    public static void main() {
        System.out.print("Falsa main (void)\n");
    }

    public static int main(int n) {
        System.out.print("Falsa main (int): ");
        System.out.print(n);
        System.out.print("\n");
        return n * 2;
    }

    public static void main(String[] args) {
        System.out.print("Verdadeira main arrancou!\n");

        main();

        int resultado;
        resultado = main(42);

        System.out.print("Resultado da falsa: ");
        System.out.print(resultado);
        System.out.print("\n");

        if (resultado == 84) {
            System.out.print("Tudo certo, vou sair mais cedo com um return vazio!\n");
            return;
        }

        System.out.print("Se vires isto, o if falhou.\n");
    }
}
