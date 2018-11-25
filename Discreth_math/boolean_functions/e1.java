import java.io.*;
import java.util.*;
import java.lang.Math;


public class e1 {
    static int dfs(int[][] ar, int numb)  {
        int[] depth = new int[numb];
        for (int k = 0; k < 5; k++) {    
            for (int i = 0; i < numb; i++) {
                if (ar[i] != null) {
                    int max = 0;
                    for (int j = 0; j < ar[i].length; j++) {
                        if (max < depth[ar[i][j]]) {
                            max = depth[ar[i][j]];
                        }
                    }
                    depth[i] = max + 1; 
                }
            }
        }
        return depth[numb - 1] + 1;
    }
    static int ans(int[][] ar, int numb, int[] value,int[][] table)  {
        for (int i = 0; i < numb; i++ ) {
            if (ar[i] != null) {
                int count = ar[i].length;
                int per = 0;
                for (int j = 0; j < count; j++) {
                    per = (per<<1) + value[ar[i][j]];
                }
                value[i] = table[i][per];
            }
        }
        return value[numb -1];
    }
    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);        
            int n = in.nextInt();
            int[][] tree = new int[n][];
            int[][] table = new int[28][];
            int[] values = new int[n];
            int[] adrs = new int[28];
            int count0 = 0;
            for (int i = 0; i < n; i++) {
                int k = in.nextInt();
                values[i] = -1;
                if (k > 0) {
                    int pow = (int)Math.pow(2, k);
                    int[] ar = new int[k];
                    for (int j = 0; j < k; j++) {
                        ar[j] = in.nextInt() - 1;
                    }
                    tree[i] = ar;
                    int[] str = new int[pow];
                    for (int j = 0; j < pow; j++) {
                        str[j] = in.nextInt();
                    }
                    table[i] = str;
                } else {
                    adrs[count0] = i;
                    count0++;
                }
            }
            System.out.println(dfs(tree, n) - 1);
            StringBuilder str0 = new StringBuilder();
            int pow = (int)Math.pow(2, count0);
            int pow1 = pow - 1 ;
            StringBuilder answer = new StringBuilder();
            for (int i = 0; i < pow; i++){
                for (int j = count0 - 1; j >= 0; j--) {
                    values[adrs[count0 - j - 1]] = (i >> j) & 1;
                }
                answer.append(ans(tree, n , values, table));
            }
            System.out.println(answer.toString());
            /*System.out.println(saves0(s));
            System.out.println(saves1(s));
            System.out.println(doubling(s));
            System.out.println(monotone(s));
            System.out.println(line(s)); */
                
    }
}
