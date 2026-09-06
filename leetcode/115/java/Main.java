


public class Main {

    public static void main(String[] args){

        String s = "babgbag";
        String t = "bag";

        System.out.println("For s=" + s + ", t=" + t + ": " + subsequencesOfSEqualT(s, t));

    }

    private static int nSubsequences(String s, String t, int s_char_index, int t_char_index, Integer[][] memo){

        int toReturn = 0;

        System.out.println( ("    ".repeat(t_char_index)) + "Starting to look in char " + s.charAt(s_char_index) + " (index " + s_char_index + ") for char " + t.charAt(t_char_index) + " (index " + t_char_index + ")");


        // we move the pointer to s until we find a match to the current pointer to t
        for(int s_index = s_char_index; s_index < s.length(); s_index++) {

            //if we already computed this solution
            if (memo[s_index][t_char_index] != null){
                System.out.println(("    ".repeat(t_char_index)) + "We already tried s index " + s_index + " and t index " + t_char_index + " pair, with value " + memo[s_index][t_char_index]);
                toReturn += memo[s_index][t_char_index];

            //if we have yet to compute this solution
            }else {

                //when we find a match
                if(s.charAt(s_index) == t.charAt(t_char_index)){

                    System.out.println(("    ".repeat(t_char_index)) + "Found match in (index " + s_char_index + ") for char " + t.charAt(t_char_index) + " (index " + t_char_index + ")");

                    //if the pointer to t is pointing to its last char, we've found a valid subsequence
                    if(t_char_index == t.length() - 1) {
                        System.out.println(("    ".repeat(t_char_index)) + "It is a full match");
                        memo[s_index][t_char_index] = 1;
                    }

                    //if we are still to reach the end of t, we match these chars and continue the search
                    else
                        memo[s_index][t_char_index] = nSubsequences(s, t, s_index + 1, t_char_index + 1, memo);

                }else {

                    memo[s_index][t_char_index] = 0;
                }

                toReturn += memo[s_index][t_char_index];


            }

        }


        return toReturn;

    }

    public static int subsequencesOfSEqualT(String s, String t){

        System.out.println("How many time can '" + t + "' be constructed with subsquences of '" + s + "'");

        //represents memory of already computed pairs
        Integer[][] memo = new Integer[s.length()][t.length()];

        return nSubsequences(s, t, 0, 0, memo);

    }

}