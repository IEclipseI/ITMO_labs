import java.io.*;
import java.util.*;
import java.lang.Math;


public class e {
    static int dfs(int[][] ar, int numb)  {
        int length = 1;
        int max = 0;
        if (ar[numb] != null) {
            int tmp;
            for (int i = 0; i < ar[numb].length; i++) {
                tmp = dfs(ar, ar[numb][i]);
                if (tmp > max) {
                    max = tmp;
                }
            }
        }
        return length + max;
    }
    static int ans(int[][] ar, int numb, int[] value,String[] table)  {
        if (value[numb] == -1) {
            StringBuilder per = new StringBuilder();
            for (int i = 0; i < ar[numb].length; i++) {
                per.append(ans(ar, ar[numb][i], value, table));
            }
            //System.out.println((int)table[numb].charAt(Integer.parseInt(per.toString(), 2)) - 48);
            value[numb] = (int)table[numb].charAt(Integer.parseInt(per.toString(), 2)) - 48;
        }
        int tmp = value[numb];
        value[numb] = -1;
        return tmp;
    }
    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);        
            int n = in.nextInt();
            int[][] tree = new int[n][];
            String[] table = new String[28];
            int[] values = new int[n];
            int[] adrs = new int[28];
            int count0 = 0;
            for (int i = 0; i < n; i++) {
                int k = in.nextInt();
                values[i] = -1;
                if (k > 0) {
                    int[] ar = new int[k];
                    int[] f = new int[(int)Math.pow(2, k)];
                    for (int j = 0; j < k; j++) {
                        ar[j] = in.nextInt() - 1;
                    }
                    tree[i] = ar;
                    StringBuilder str = new StringBuilder();
                    int pow = (int)Math.pow(2, k);
                    for (int j = 0; j < pow; j++) {
                        str.append(in.nextInt());
                    }
                    table[i] = str.toString();
                } else {
                    adrs[count0] = i;
                    count0++;
                }
            }
            System.out.println(dfs(tree, n - 1) - 1);
            StringBuilder str0 = new StringBuilder();
            for (int i = 0; i < Integer.toString((int)Math.pow(2, count0) - 1, 2).length(); i++) {
                str0.append('0');
            }
            int pow = (int)Math.pow(2, count0);
            StringBuilder answer = new StringBuilder();
            for (int i = 0; i < pow; i++){
                String s = Integer.toString(i, 2);
                s =  str0.substring(0, str0.length() - s.length()) + s;
                for (int j = 0; j < count0; j++) {
                    values[adrs[j]] = s.charAt(j) - 48; 
                }
                answer.append(ans(tree, n - 1, values, table));
            }
            System.out.println(answer.toString());
            /*System.out.println(saves0(s));
            System.out.println(saves1(s));
            System.out.println(doubling(s));
            System.out.println(monotone(s));
            System.out.println(line(s)); */
                
    }
}
