import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Main{

    static final long MOD = 1_000_000_007L;

    public static int cost_of_cut(int n, List<Integer> cuts, int index_of_cut, int ident_level) {

        String ident_string = "  ".repeat(ident_level);
        System.out.println();
        System.out.println(ident_string + "Processing cut in index " + cuts.get(index_of_cut) + " on size " + n);

        List<Integer> new_left_cuts = new ArrayList<Integer>(cuts.size() - 1);
        List<Integer> new_right_cuts = new ArrayList<Integer>(cuts.size() - 1);

        int new_left_length = cuts.get(index_of_cut);
        int new_right_length = n - new_left_length;

        for(int i = 0; i < cuts.size(); i++){

            if(i != index_of_cut){

                if(cuts.get(i) > new_left_length){
                    new_right_cuts.add(cuts.get(i) - new_left_length);

                }else{
                    new_left_cuts.add(cuts.get(i));
                }

            }
        }

        System.out.println(ident_string + " Left cut:");
        int left_cut = min_cost(new_left_length, new_left_cuts, ident_level + 1);

        System.out.println(ident_string + " Right cut:");
        int right_cut = min_cost(new_right_length, new_right_cuts, ident_level + 1);

        int total = n + left_cut + right_cut;
        System.out.println(ident_string + " Total cut: " + total);

        return total;
    }

    public static int min_cost(int n, List<Integer> cuts, int ident_level) {

        String ident_string = "  ".repeat(ident_level);
        System.out.println();
        System.out.println(ident_string + "Processing on size " + n + " cuts: " + cuts);

        if(cuts.isEmpty()){
            System.out.println(ident_string + "There were no cuts, so cost is 0");
            return 0;
        }
        else if(cuts.size() == 1){
            System.out.println(ident_string + "There was only one cut, so cost is " + n);
            return n;

        }else{
            int current_min_result = Integer.MAX_VALUE;

            for(int i = 0; i < cuts.size(); i++){
                current_min_result = Math.min(cost_of_cut(n, cuts, i, ident_level + 1), current_min_result);
            }
            System.out.println(ident_string + "Min cost was: " + current_min_result);
            return current_min_result;
        }
    }

    public static int minCost(int n, int[] cuts) {

        List<Integer> new_cuts = new ArrayList<Integer>(cuts.length);

        for(int i = 0; i < cuts.length; i++){
            new_cuts.add(cuts[i]);
        }

        return min_cost(n, new_cuts, 0);
    }

    public static void main(String[] args) {

        int n = 7;
        int[] cuts = {1, 3, 4, 5};

        int result = minCost(n, cuts);
        System.out.println();

        System.out.println("Result for " + n + " and cuts " + Arrays.toString(cuts) + ": " + result);

    }

}

