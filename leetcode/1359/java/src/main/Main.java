
public class Main{

    static final long MOD = 1_000_000_007L;

    public static long countOrders(int n, int ident_level) {

        String ident_string = "  ".repeat(ident_level - n);
        System.out.println();

        if (n == 1) {

            System.out.println(ident_string + "For n = " + n + ", only order is {P1, D1}, 1");

            return 1;

        } else {

            int to_return = 0;

            for (int i = 1; i < n * 2; i++) {

                System.out.println(ident_string + "For n = " + n + ", testing for D1 in " + i + " different positions");

                to_return += i;
            }

            System.out.println();
            System.out.println(ident_string + "For n = " + n + ", there are " + to_return + " possible configurations for P1 and D1");

            return to_return * countOrders(n - 1, ident_level);

        }

    }

    public static void main(String[] args) {

        int n = 8;

        long result = countOrders(n, n);
        System.out.println();

        System.out.println("Result for " + n + ": " + result);

        System.out.println("Mod result for " + n + ": " + (result % MOD));
    }

}

