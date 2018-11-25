import java.io.*;
import java.util.*;
import java.lang.Math;
import javafx.util.*;

public class a1 {
    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int m = in.nextInt();
        Set <Pair <Integer, Integer>> a = new HashSet<Pair<Integer, Integer>>();
        for (int i = 0; i < m; i++) {
            Pair<Integer, Integer> pair = new Pair<Integer, Integer>(in.nextInt(),in.nextInt());
            a.add(pair);
        }
        boolean flag = false;
        StringBuilder str0 = new StringBuilder();
        for (int i = 0; i < Integer.toString((int)Math.pow(2, n) - 1, 2).length(); i++) {
            str0.append('0');
        }
        for (int i = 0; i < Math.pow(2, n); i++) {
            String s = Integer.toString(i, 2);
            s =  str0.substring(0, str0.length() - s.length()) + s;
            //System.out.print(s + " ");
            boolean value = true;
            for (Pair<Integer, Integer> pair: a) {
                int sum = 0;

                if (s.charAt(Math.abs(pair.getKey()) - 1) == '0' && pair.getKey() < 0 ) {
                    sum++;
                }
                if (s.charAt(Math.abs(pair.getKey()) - 1) == '1' && pair.getKey() > 0 ) {
                    sum++;
                }
                if (s.charAt(Math.abs(pair.getValue()) - 1) == '0' && pair.getValue() < 0 ) {
                    sum++;
                }
                if (s.charAt(Math.abs(pair.getValue()) - 1) == '1' && pair.getValue() > 0 ) {
                    sum++;
                }
                if (sum == 0) {
                    value = false;
                }
            }
            if (value) {
                flag = value;
                break;
            } 
        }
        if (flag) {
            System.out.println("NO");
        } else {
            System.out.println("YES");
        }
            /*System.out.println(saves0(s));
            System.out.println(saves1(s));
            System.out.println(doubling(s));
            System.out.println(monotone(s));
            System.out.println(line(s)); */
        //System.out.println(ar);        
    }
}
