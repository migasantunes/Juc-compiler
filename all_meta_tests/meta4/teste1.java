class Teste1 {
    public static int fluxo(int val) {
        if (val > 10) {
            if (val > 20) {
                return 20;
            }
            return 10;
        } else {
            int a;
            a = 5;
            while (a > 0) {
                if (a == 2) {
                    return 2;
                }
                a = a - 1;
            }
        }
        return 0;
    }

    public static void main(String[] args) {
        System.out.print(fluxo(25));
        System.out.print(fluxo(15));
        System.out.print(fluxo(5));
    }
}