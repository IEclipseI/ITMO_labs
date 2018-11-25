import java.io.*;
import java.util.*;
import java.lang.Math;


public class a {
    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int[][] ar = new int[2 * n][2 * n];
        int k = in.nextInt();
        int tmp1;
        int tmp2;
        for (int i = 0; i < k; i++) {
            tmp1 = in.nextInt();
            tmp2 = in.nextInt();
            if (tmp1 > 0) {
                if (tmp2 > 0) {
                    ar[n - 1 + tmp1][tmp2 - 1] = 1;
                    ar[n - 1 + tmp2][tmp1 - 1] = 1;
                } else {
                    ar[n - 1 + tmp1][n - tmp2 - 1] = 1;
                    ar[-1 - tmp2][tmp1 - 1] = 1;
                }
            } else {
                if (tmp2 > 0) {
                    ar[-tmp1 - 1][tmp2 - 1] = 1;
                    ar[n - 1 + tmp2][-tmp1 - 1] = 1;                
                } else {
                    ar[tmp1 - 1][tmp2 - 1] = 1;
                }
            }
        }    
            /*System.out.println(saves0(s));
            System.out.println(saves1(s));
            System.out.println(doubling(s));
            System.out.println(monotone(s));
            System.out.println(line(s)); */
        System.out.println(ar);        
    }
}
